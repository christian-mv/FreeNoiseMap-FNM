#ifndef FNM_CORE_NOISE_ENGINE_H
#define FNM_CORE_NOISE_ENGINE_H

#include <vector>
#include <random>
#include <Eigen/Core>
#include "point_source.h"
#include "line_source_segment.h"
#include "point_receiver.h"
#include "barrier_segment.h"

namespace fnm_core {

using MatrixOfDoubles = std::vector<std::vector<double>>;

namespace NoiseEngine {
    
    // Physical Constants
    constexpr double SoundSpeed = 343.2;

    /**
     * @brief Main Point-to-Point calculation.
     * Computes divergence and barrier attenuation, adding the result energetically to the receiver.
     */
    void P2P(const PointSource &pointSource, PointReceiver &receiver,
             const std::vector<const BarrierSegment*> &barrierSegments);

    /**
     * @brief Discretizes a line source into point sources.
     */
    std::vector<PointSource> fromLineToPointSources(const LineSourceSegment *line,
                                                    const double &maxDistanceBetweenPoints);

    /**
     * @brief Calculates total barrier attenuation using a Smooth Continuous Model.
     * Combines top and lateral diffraction energetically.
     */
    double attenuation_barrier(const PointSource* const pointSource,
                               const PointReceiver* const receiver,
                               const std::vector<const BarrierSegment*> &barrierSegments,
                               const double &frequency);

    /**
     * @brief Standard geometric divergence (A_div).
     */
    double attenuation_divergence(const double &distance);

    // Utilities
    double sumdB(const double &Leq1, const double &Leq2);
    double distanceBetweenPoints(double x1, double y1, double z1, double x2, double y2, double z2);
    
    // Legacy/Helper utilities preserved for compatibility
    MatrixOfDoubles createMatrixOfDoubles(unsigned int m, unsigned int n);
    int intRandom(int min, int max);
    void interpolationValueAt(const double &t1, const double &y1,
                              const double &t2, double &y2,
                              const double &t3, const double &y3);
}
}

#endif // FNM_CORE_NOISE_ENGINE_H
