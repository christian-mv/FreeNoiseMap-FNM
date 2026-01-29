#include "noise_engine.h"
#include <chrono>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <random>
#include <map>

namespace fnm_core {
namespace NoiseEngine {

// =========================================================
// GEOMETRY HELPERS
// =========================================================

static bool isSamePoint2D(const Eigen::Vector2d& p1, const Eigen::Vector2d& p2, double eps = 1e-2) {
    return (p1 - p2).squaredNorm() < eps * eps;
}

// Strict intersection (excludes endpoints)
static bool segmentsIntersectStrict(const Eigen::Vector2d& A, const Eigen::Vector2d& B,
                                    const Eigen::Vector2d& C, const Eigen::Vector2d& D) {
    auto cross = [](const Eigen::Vector2d& u, const Eigen::Vector2d& v) {
        return u.x() * v.y() - u.y() * v.x();
    };
    double d1 = cross(B - A, C - A);
    double d2 = cross(B - A, D - A);
    double d3 = cross(D - C, A - C);
    double d4 = cross(D - C, B - C);
    return (((d1 > 1e-9 && d2 < -1e-9) || (d1 < -1e-9 && d2 > 1e-9)) &&
            ((d3 > 1e-9 && d4 < -1e-9) || (d3 < -1e-9 && d4 > 1e-9)));
}

/**
 * @brief Checks if the path from P1 to P2 is blocked by any barrier in the given set.
 * Used to verify if a diffraction edge is actually illuminated.
 */
static bool isPathBlocked(const Eigen::Vector2d& P1, const Eigen::Vector2d& P2,
                          const std::vector<const BarrierSegment*>& barriers,
                          const BarrierSegment* ignoreSeg = nullptr) {
    for (const auto* seg : barriers) {
        if (seg == ignoreSeg) continue;
        if (segmentsIntersectStrict(P1, P2, Eigen::Vector2d(seg->get_x1(), seg->get_y1()), 
                                            Eigen::Vector2d(seg->get_x2(), seg->get_y2()))) {
            return true;
        }
    }
    return false;
}

static Eigen::Vector3d findDiffractionPoint(const Eigen::Vector3d& S, const Eigen::Vector3d& R,
                                            const Eigen::Vector3d& E1, const Eigen::Vector3d& E2) {
    auto pathLen = [&](double t) {
        Eigen::Vector3d P = E1 + t * (E2 - E1);
        return (S - P).norm() + (P - R).norm();
    };

    double l = 0.0, r = 1.0;
    for(int i = 0; i < 32; ++i) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        if(pathLen(m1) < pathLen(m2)) r = m2;
        else l = m1;
    }
    return E1 + ((l + r) / 2.0) * (E2 - E1);
}

static double calculateContinuousDz(const Eigen::Vector3d& S, const Eigen::Vector3d& R, 
                                    const Eigen::Vector3d& P, double lambda) {
    double d_ss = (S - P).norm();
    double d_sr = (P - R).norm();
    double d_dir = (S - R).norm();
    double delta = (d_ss + d_sr) - d_dir;

    if (delta <= 1e-9) return 0.0;

    double k_met = 1.0;
    if (delta > 1e-5) {
        double val = (d_ss * d_sr * d_dir) / (2.0 * delta);
        if (val > 0) k_met = std::exp(-(1.0/2000.0) * std::sqrt(val));
    }

    double C2 = 20.0;
    double arg = 1.0 + (C2 / lambda) * delta * k_met;
    return 10.0 * std::log10(std::max(1.0, arg));
}

// =========================================================
// MAIN ENGINE IMPLEMENTATION
// =========================================================

void P2P(const PointSource &pointSource, PointReceiver &receiver,
         const std::vector<const BarrierSegment*> &barrierSegments) {
    
    double dist = distanceBetweenPoints(pointSource.get_x(), pointSource.get_y(), pointSource.get_z(),
                                        receiver.get_x(), receiver.get_y(), receiver.get_z());

    double A_div = attenuation_divergence(dist);
    double A_bar = 0;

    if (!barrierSegments.empty()) {
        A_bar = attenuation_barrier(&pointSource, &receiver, barrierSegments, 500.0);
    }

    double level = pointSource.get_Lw() - A_div - A_bar;
    receiver.set_Leq(sumdB(receiver.get_Leq(), level));
}

double attenuation_barrier(const PointSource* const pointSource,
                           const PointReceiver* const receiver,
                           const std::vector<const BarrierSegment*> &barrierSegments,
                           const double &frequency) {
    
    Eigen::Vector3d S(pointSource->get_x(), pointSource->get_y(), pointSource->get_z());
    Eigen::Vector3d R(receiver->get_x(), receiver->get_y(), receiver->get_z());
    Eigen::Vector2d S2(S.x(), S.y()), R2(R.x(), R.y());
    double lambda = SoundSpeed / frequency;

    // 1. Identify DIRECTLY obstructing segments
    std::vector<const BarrierSegment*> obstructing;
    for (auto* seg : barrierSegments) {
        if (segmentsIntersectStrict(S2, R2, Eigen::Vector2d(seg->get_x1(), seg->get_y1()), 
                                            Eigen::Vector2d(seg->get_x2(), seg->get_y2()))) {
            obstructing.push_back(seg);
        }
    }

    if (obstructing.empty()) return 0.0; // Illuminated Zone

    // 2. Top Diffraction (Dominant Path)
    // We calculate the attenuation for all obstructing barriers and pick the MAX.
    // This implicitly handles "barrier behind barrier" for top diffraction:
    // the most effective one sets the attenuation floor.
    double maxDzTop = 0.0;
    for (auto* seg : obstructing) {
        Eigen::Vector3d B1(seg->get_x1(), seg->get_y1(), seg->get_z1() + seg->get_height());
        Eigen::Vector3d B2(seg->get_x2(), seg->get_y2(), seg->get_z2() + seg->get_height());
        Eigen::Vector3d P = findDiffractionPoint(S, R, B1, B2);
        
        double dz = calculateContinuousDz(S, R, P, lambda);
        if (dz > maxDzTop) maxDzTop = dz;
    }

    // 3. Lateral Diffraction
    // Group obstructing segments into chains to find lateral edges
    std::set<const BarrierSegment*> processed;
    double transmissionLateralSum = 0.0;

    for (auto* startSeg : obstructing) {
        if (processed.count(startSeg)) continue;

        // Flood-fill to find connected chain
        std::set<const BarrierSegment*> chain;
        std::queue<const BarrierSegment*> q;
        q.push(startSeg); chain.insert(startSeg); processed.insert(startSeg);

        while (!q.empty()) {
            auto* curr = q.front(); q.pop();
            Eigen::Vector2d c1(curr->get_x1(), curr->get_y1()), c2(curr->get_x2(), curr->get_y2());

            for (auto* other : barrierSegments) {
                if (chain.count(other)) continue;
                Eigen::Vector2d o1(other->get_x1(), other->get_y1()), o2(other->get_x2(), other->get_y2());
                if (isSamePoint2D(c1, o1) || isSamePoint2D(c1, o2) || 
                    isSamePoint2D(c2, o1) || isSamePoint2D(c2, o2)) {
                    chain.insert(other);
                    processed.insert(other);
                    q.push(other);
                }
            }
        }

        // Identify Endpoints
        struct Node { Eigen::Vector2d p; double z; double h; int degree = 0; };
        std::vector<Node> nodes;
        auto addNode = [&](const Eigen::Vector3d& pos, double h) {
            Eigen::Vector2d pos2(pos.x(), pos.y());
            for (auto& n : nodes) if (isSamePoint2D(n.p, pos2)) { n.degree++; return; }
            nodes.push_back({pos2, pos.z(), h, 1});
        };

        for (auto* seg : chain) {
            addNode(Eigen::Vector3d(seg->get_x1(), seg->get_y1(), seg->get_z1()), seg->get_height());
            addNode(Eigen::Vector3d(seg->get_x2(), seg->get_y2(), seg->get_z2()), seg->get_height());
        }

        // Calculate Lateral Attenuation
        for (const auto& n : nodes) {
            if (n.degree == 1) { // Lateral Edge
                
                // CRITICAL FIX: Check Upstream Occlusion
                // Is the path from Source to this Edge blocked by ANOTHER barrier?
                if (isPathBlocked(S2, n.p, barrierSegments)) {
                    continue; // This edge is in shadow, ignore it
                }
                
                // Also check downstream: Edge to Receiver blocked?
                if (isPathBlocked(n.p, R2, barrierSegments)) {
                    continue; // Receiver can't "see" this edge directly
                }

                Eigen::Vector3d Base(n.p.x(), n.p.y(), n.z);
                Eigen::Vector3d Top = Base + Eigen::Vector3d(0, 0, n.h);
                
                Eigen::Vector3d P = findDiffractionPoint(S, R, Base, Top);
                double dzLat = calculateContinuousDz(S, R, P, lambda);
                
                transmissionLateralSum += std::pow(10.0, -dzLat / 10.0);
            }
        }
    }

    // 4. Combine
    double transmissionTop = std::pow(10.0, -maxDzTop / 10.0);
    double totalTransmission = transmissionTop + transmissionLateralSum;

    if (totalTransmission > 1.0) totalTransmission = 1.0;

    return -10.0 * std::log10(totalTransmission);
}

std::vector<PointSource> fromLineToPointSources(const LineSourceSegment *line,
                                                const double &maxDistanceBetweenPoints) {
    std::vector<PointSource> results;
    double totalLen = line->distance();
    if (totalLen <= 0) return results;

    int n = std::max(1, static_cast<int>(std::ceil(totalLen / maxDistanceBetweenPoints)));
    results.reserve(n + 1);

    double dx = (line->get_x2() - line->get_x1()) / n;
    double dy = (line->get_y2() - line->get_y1()) / n;
    double dz = (line->get_z2() - line->get_z1()) / n;
    double dw = line->get_Lw_total() - 10.0 * std::log10(n + 1);

    for (int i = 0; i <= n; ++i) {
        PointSource p;
        p.set_x(line->get_x1() + i * dx);
        p.set_y(line->get_y1() + i * dy);
        p.set_z(line->get_z1() + i * dz);
        p.set_Lw(dw);
        results.push_back(p);
    }
    return results;
}

double attenuation_divergence(const double &distance) {
    return (distance < 1.0) ? 0.0 : (20.0 * std::log10(distance) + 11.0);
}

double sumdB(const double &Leq1, const double &Leq2) {
    return 10.0 * std::log10(std::pow(10.0, 0.1 * Leq1) + std::pow(10.0, 0.1 * Leq2));
}

double distanceBetweenPoints(double x1, double y1, double z1, double x2, double y2, double z2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2));
}

// Legacy Helpers
void interpolationValueAt(const double &t1, const double &y1,
                          const double &t2, double &y2,
                          const double &t3, const double &y3) {
    if (std::abs(t3 - t1) < 1e-9) { y2 = y1; return; }
    y2 = ((t2 - t1) * (y3 - y1) / (t3 - t1)) + y1;
}

MatrixOfDoubles createMatrixOfDoubles(unsigned int m, unsigned int n) {
    return MatrixOfDoubles(m, std::vector<double>(n, 0.0));
}

int intRandom(int min, int max) {
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(min, max)(gen);
}

} // namespace NoiseEngine
} // namespace fnm_core
