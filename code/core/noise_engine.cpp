#include "noise_engine.h"
#include <chrono>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <Eigen/Core>
using namespace std;

namespace fnm_core {
namespace NoiseEngine
{
MatrixOfDoubles createMatrixOfDoubles(unsigned int m, unsigned int n){
    MatrixOfDoubles myMatriz;

    //m * n is the size of the matrix

    //Grow rows by m
    myMatriz.resize(m);
    for(unsigned int i = 0 ; i < m ; ++i)
    {
        //Grow Columns by n
        myMatriz[i].resize(n);
    }
    //Now you have matrix m*n with default values
    return myMatriz;
}

// this function generate a integer random
int intRandom(int min, int max)
{
    static std::mt19937 generator = []() {
        std::mt19937 gen;
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        gen.seed(static_cast<unsigned int>(seed));
        return gen;
    }();
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}


double distanceBetweenPoints(double x1, double y1, double z1, double x2, double y2, double z2)
{
    return (Eigen::Vector3d(x2, y2, z2) - Eigen::Vector3d(x1, y1, z1)).norm();
}



void P2P(fnm_core::PointSource *pointSource,
         fnm_core::PointReceiver *receiver,
         const std::vector<fnm_core::BarrierSegment*> &barrierSegments)
{
    double distance = distanceBetweenPoints(pointSource->get_x(),
                                            pointSource->get_y(),
                                            pointSource->get_z(),
                                            receiver->get_x(),
                                            receiver->get_y(),
                                            receiver->get_z());

    double A_div = attenuation_divergence(distance);

    double A_bar = 0;

    if(!barrierSegments.empty()){
        A_bar = attenuation_barrier(pointSource,receiver,barrierSegments, 500.0);
    }


    double Leq_result = pointSource->get_Lw() - A_div - A_bar;
    Leq_result = sumdB(receiver->get_Leq(), Leq_result);

    receiver->set_Leq(Leq_result);
    //        qDebug()<<"(X,Y,Leq): ("<<receiver->get_x()<<
    //                  ","<<receiver->get_y()<<
    //                  ","<<receiver->get_Leq()<<")";
}

double sumdB(const double &Leq1, const double &Leq2)
{
    return 10.0*log10( pow(10.0,(0.1*Leq1)) + pow(10.0,(0.1*Leq2)) );
}


// this function modifies y2 according to: https://ncalculators.com/geometry/linear-interpolation-calculator.htm
void interpolationValueAt(const double &t1,
                          const double &y1,
                          const double &t2,
                          double &y2,
                          const double &t3,
                          const double &y3)
{
    y2 = ((t2 - t1)*(y3 - y1) / (t3 - t1)) + y1;
}



int greatestIntegerFunction(int x, int dx, int dy)
{
    /*
     * Optimized implementation of the greatest integer function logic.
     * Returns ceil(x / dx) * dy
     * NOTE: Assumes x > 0 as per original implementation comments.
     */
    if (x <= 0) return 0; // Handle potential out of bound based on original logic
    int i = (x - 1) / dx;
    return (i + 1) * dy;
}


std::vector<fnm_core::PointSource> fromLineToPointSources(const fnm_core::LineSourceSegment *line,
                                                       const double &distanceBetweenPoints)
{
    std::vector<fnm_core::PointSource> results;
    int n = static_cast<int>(line->distance()/distanceBetweenPoints);
    results.reserve(n + 1);
    
    double dx = line->get_x2() - line->get_x1();
    double dy = line->get_y2() - line->get_y1();
    double dz = line->get_z2() - line->get_z1();
    double dw = line->get_Lw_total() - 10.0*log10(n); // Lw per point source

    fnm_core::PointSource point;
    for(int k=0; k<=n; k++){
        point.set_x( line->get_x1() + k*dx/n );
        point.set_y( line->get_y1() + k*dy/n );
        point.set_z( line->get_z1() + k*dz/n );
        point.set_Lw(dw);
        results.push_back(point);
    }
    return results;
}

double attenuation_divergence(const double &distance)
{
    double A_div;
    distance<1 ? A_div=0 : A_div = 20*std::log10(distance) + 11;
    return A_div;
}

double attenuation_barrier(const fnm_core::PointSource* const pointSource,
                           const fnm_core::PointReceiver* const receiver,
                           const std::vector<fnm_core::BarrierSegment*> &barrierSegments,
                           const double &frequency)
{

    double  z, kmet, C2, C3, lambda, Dz;
    std::vector<Eigen::Vector3d> diffractionPath;

    diffractionPath =  calculateDiffractionPathPoints(pointSource->get_x(),
                                                pointSource->get_y(),
                                                pointSource->get_z(),
                                                receiver->get_x(),
                                                receiver->get_y(),
                                                receiver->get_z(),
                                                barrierSegments);

    if(diffractionPath.size()<=2){
        return 0;
    }

    IsoBarrierPathdistances isoDistances;
    isoDistances = Iso9613BarrierDistances(diffractionPath);


    z = isoDistances.dss + isoDistances.dsr + isoDistances.e- isoDistances.d;

    // correct sign for z according to sightlight (pending)


//    z>0 ? kmet = std::pow( euler , -(1/2000)*std::sqrt(diffractionDistance*d/(2*z)) ) : kmet = 1;
    z>0 ? kmet = std::pow( euler , -(1/2000)*std::sqrt(isoDistances.dss*isoDistances.dsr*isoDistances.d/(2*z)) ) : kmet = 1;

    C2 = 20; // see ISO 9613
    C3 = 1; // single difraction
    // C3 for double difraction see equation 15 ISO 9613-2


    lambda = c/frequency;

    Dz = 10*std::log10( 3 + (C2/lambda)*C3*z*kmet );

    return Dz;
}


std::tuple<bool, double, double> intersectionBetween2DLineSegments(double p0x, double p0y,
                                                 double p1x, double p1y,
                                                 double p2x, double p2y,
                                                 double p3x, double p3y)
{
    // https://www.youtube.com/watch?v=4bIsntTiKfM&list=PL7wAPgl1JVvURU_YF4hHMcsWK98KbnZPs&index=2

    double intersectX, intersectY;
    double A1, B1, C1, A2, B2, C2, denominator;
    double rx0, ry0, rx1, ry1;

    A1 = p1y - p0y;
    B1 = p0x - p1x;
    C1 = A1 * p0x + B1 * p0y;
    A2 = p3y - p2y;
    B2 = p2x - p3x;
    C2 = A2 * p2x + B2 * p2y;
    denominator = A1*B2 - A2*B1;

    if(denominator == 0  || areTheseParallelLines(p0x, p0y,p1x, p1y,p2x, p2y,p3x, p3y)){
        return std::make_tuple(false, 0, 0);
    }

    intersectX = (B2*C1 - B1*C2)/denominator;
    intersectY = (A1*C2 - A2*C1)/denominator;

    rx0 = (intersectX - p0x) / (p1x - p0x);
    ry0 = (intersectY - p0y) / (p1y - p0y);
    rx1 = (intersectX - p2x) / (p3x - p2x);
    ry1 = (intersectY - p2y) / (p3y - p2y);

    if(((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) &&
            ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))) {
        return std::make_tuple(true, intersectX, intersectY);
    }
    else {
        return std::make_tuple(false, 0, 0);
    }

}

bool areTheseParallelLines(double p0x, double p0y, double p1x, double p1y,
                           double p2x, double p2y, double p3x, double p3y)
{
    // Precalculus 7Ed, chapter 1; James Stewart
    double m1, m2;
    m1 = (p1y - p0y)/(p1x - p0x);
    m2 = (p3y - p2y)/(p3x - p2x);
    return (m1 == m2);
}

std::vector<Eigen::Vector3d> calculateDiffractionPathPoints(const double &x0, const double &y0, const double &z0,
                                                                           const double &x1, const double &y1, const double &z1,
                                                                           const std::vector<fnm_core::BarrierSegment*> &barrierSegments)
{
    std::vector<Eigen::Vector3d> pathPoints;
    // Reserve memory: start + end + barriers (approx)
    pathPoints.reserve(barrierSegments.size() + 2);

    std::tuple<bool, double, double> intersection;
    Eigen::Vector3d startPoint(x0, y0, z0);
    pathPoints.push_back(startPoint);

    for(auto segment: barrierSegments){
        intersection = intersectionBetween2DLineSegments(x0,y0,x1,y1,
                                                         segment->get_x1(),
                                                         segment->get_y1(),
                                                         segment->get_x2(),
                                                         segment->get_y2());

        // take into account point that are positive intersections
        if(std::get<0>(intersection)){
            pathPoints.emplace_back(std::get<1>(intersection),
                                    std::get<2>(intersection),
                                    segment->get_height());
        }
    }

    pathPoints.emplace_back(x1,y1,z1);

    // sort vector according to 2D distance from point x0,y0
    // Optimization: Compare squared distances to avoid sqrt
    std::sort(pathPoints.begin() + 1, // Start sorting after the first point (source)
              pathPoints.end() - 1,   // Don't include the last point (receiver) - wait, barriers need to be sorted between source and receiver
              [&startPoint](const Eigen::Vector3d &a, const Eigen::Vector3d &b) -> bool{
        
        // 2D distance squared: (x-x0)^2 + (y-y0)^2
        double distA = (a.head<2>() - startPoint.head<2>()).squaredNorm();
        double distB = (b.head<2>() - startPoint.head<2>()).squaredNorm();

        return distA < distB;
    });
    
    // Note: The original code sorted ALL points including source and receiver based on distance from source.
    // Since source is at distance 0, it stays first. Receiver is furthest? Not necessarily if path goes back, but usually yes.
    // To be safe and identical to original behavior, we sort the whole range.
    std::sort(pathPoints.begin(), pathPoints.end(),
              [&startPoint](const Eigen::Vector3d &a, const Eigen::Vector3d &b) -> bool{
        double distA = (a.head<2>() - startPoint.head<2>()).squaredNorm();
        double distB = (b.head<2>() - startPoint.head<2>()).squaredNorm();
        return distA < distB;
    });

    return pathPoints;
}


// for this function it is supposed that pathPoints is already sorted
IsoBarrierPathdistances Iso9613BarrierDistances(const std::vector<Eigen::Vector3d> &pathPoints)
{

    IsoBarrierPathdistances data;


    int lastIndex = pathPoints.size()-1;

    data.d = (pathPoints[0] - pathPoints[lastIndex]).norm();

    data.dss = (pathPoints[0] - pathPoints[1]).norm();

    data.dsr = (pathPoints[lastIndex] - pathPoints[lastIndex-1]).norm();
    
    data.e = 0;

    for(int i= 1; i<=lastIndex-2; i++){
        data.e += (pathPoints[i] - pathPoints[i+1]).norm();
    }


//    qDebug()<<"d: "<<data.d<<" dss: "<<data.dss<<" dsr: "<<data.dsr<<" e: "<<data.e;

    return data;

}


}
}; // end namespace
