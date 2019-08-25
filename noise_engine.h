#ifndef NOISE_ENGINE_H
#define NOISE_ENGINE_H

#define MATRIX_OF_DOUBLES std::vector< std::vector<double> >

#include <cstdlib>
#include <ctime>
#include <vector>
#include "minimal_point_source.h"
#include "minimal_line_source.h"
#include "single_receiver.h"
#include "receivers_grid.h"
#include "minimal_acoustic_barrier.h"


namespace  NoiseEngine
{    
    const double pi = 3.14159265359;
    const double euler = 2.71828182845;
    const double c = 343.2; // sound speed (correct later acording to ISO 9613-1 eq A5)

    MATRIX_OF_DOUBLES createMatrixOfDoubles(unsigned int m, unsigned int n);
    void initSeed(); // initializes the seed only once
    int intRandom(int min, int max);

    void P2P(MinimalPointSource *pointSource, SingleReceiver *receiver,
             const Minimal_acoustic_barrier* barrier=nullptr);


    double attenuation_divergence(const double & distance);

    double attenuation_barrier(const MinimalPointSource* const pointSource,
                               const SingleReceiver* const receiver,
                               const Minimal_acoustic_barrier* const barrierSegment,
                               const double &frequency);


    double distanceBetweenPoints(double x1, double y1, double z1,
                                 double x2, double y2, double z2);

    std::tuple<double, double> intercectionPointBetween2DLines(double p0x, double p0y,
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

    std::vector<MinimalPointSource> fromLineToPointSources(const MinimalLineSource *line,
                                                           const double &delta);



};

#endif // DYNAMIC_MATRIX_H
