#ifndef FNM_CORE_NOISE_ENGINE_H
#define FNM_CORE_NOISE_ENGINE_H

#define MATRIX_OF_DOUBLES std::vector< std::vector<double> >

#include <vector>
#include <random>
#include "point_source.h"
#include "line_source_segment.h"
#include "point_receiver.h"
#include "barrier_segment.h"


namespace fnm {
namespace  NoiseEngine
{    
    const double pi = 3.14159265359;
    const double euler = 2.71828182845;
    const double c = 343.2; // sound speed (correct later acording to ISO 9613-1 eq A5)

    struct IsoBarrierPathdistances{
        double d;
        double dss;
        double dsr;
        double e;
    };


    std::vector< std::tuple<double, double, double> > calculateDiffractionPathPoints(const double &x0, const double &y0, const double &z0,
                                                                               const double &x1, const double &y1, const double &z1,
                                                                               const std::vector<CoreBarrierSegment*> &barrierSegments);




    IsoBarrierPathdistances Iso9613BarrierDistances(const std::vector<std::tuple<double, double, double>> &pathPoints);




    MATRIX_OF_DOUBLES createMatrixOfDoubles(unsigned int m, unsigned int n);
    int intRandom(int min, int max);

    void P2P(CorePointSource *pointSource, CorePointReceiver *receiver,
             const std::vector<CoreBarrierSegment*> &barrierSegments);


    double attenuation_divergence(const double & distance);

    double attenuation_barrier(const CorePointSource* const pointSource,
                               const CorePointReceiver* const receiver,
                               const std::vector<CoreBarrierSegment*> &barrierSegments,
                               const double &frequency);


    double distanceBetweenPoints(double x1, double y1, double z1,
                                 double x2, double y2, double z2);


    // this functio returns a tuple with 3 values:
    // first value: is a boolean indicating wheter or not the lines intercet
    // second value: x coordinate of the intercetion point
    // third value: y coordinate of the intercetion point
    std::tuple<bool, double, double> intercectionBetween2DLineSegments(double p0x, double p0y,
                                                     double p1x, double p1y,
                                                     double p2x, double p2y,
                                                     double p3x, double p3y);

    bool areTheseParallelLines(double p0x, double p0y,
                               double p1x, double p1y,
                               double p2x, double p2y,
                               double p3x, double p3y);



    double sumdB(const double &Leq1, const double &Leq2);

    int greatestIntegerFunction(int x, int dx=100, int dy=25);

    void interpolationValueAt(
                            const double &t1,
                            const double &y1,
                            const double &t2,
                                  double &y2,
                            const double &t3,
                            const double &y3);

    std::vector<CorePointSource> fromLineToPointSources(const LineSourceSegment *line,
                                                           const double &delta);



};
}

#endif // DYNAMIC_MATRIX_H