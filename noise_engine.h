#ifndef NOISE_ENGINE_H
#define NOISE_ENGINE_H

#define MATRIX_OF_DOUBLES std::vector< std::vector<double> >

#include <cstdlib>
#include <ctime>
#include <vector>
#include "minimal_point_source.h"
#include "fnm_line_segment_source.h"
#include "single_receiver.h"
#include "receivers_grid.h"
#include "fnm_acoustic_barrier_segment.h"


namespace  NoiseEngine
{    
    const double pi = 3.14159265359;
    const double euler = 2.71828182845;
    const double c = 343.2; // sound speed (correct later acording to ISO 9613-1 eq A5)

    struct BarrierPathdistances{
        double d;
        double dss;
        double dsr;
        double e;
    };


    std::vector< std::tuple<double, double, double> > calculateDiffractionPathPoints(const double &x0, const double &y0, const double &z0,
                                                                               const double &x1, const double &y1, const double &z1,
                                                                               const std::vector<FnmAcousticBarrierSegment*> &barrierSegments);




    BarrierPathdistances Iso9613BarrierDistances(const std::vector<std::tuple<double, double, double>> &pathPoints);




    MATRIX_OF_DOUBLES createMatrixOfDoubles(unsigned int m, unsigned int n);
    void initSeed(); // initializes the seed only once
    int intRandom(int min, int max);

    void P2P(MinimalPointSource *pointSource, SingleReceiver *receiver,
             const std::vector<FnmAcousticBarrierSegment*> &barrierSegments);


    double attenuation_divergence(const double & distance);

    double attenuation_barrier(const MinimalPointSource* const pointSource,
                               const SingleReceiver* const receiver,
                               const std::vector<FnmAcousticBarrierSegment*> &barrierSegments,
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

    std::vector<MinimalPointSource> fromLineToPointSources(const FnmLineSegmentSource *line,
                                                           const double &delta);



};

#endif // DYNAMIC_MATRIX_H
