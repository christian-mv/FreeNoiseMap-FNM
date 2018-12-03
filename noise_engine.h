#ifndef NOISE_ENGINE_H
#define NOISE_ENGINE_H

#define MATRIX_OF_DOUBLES std::vector< std::vector<double> >

#include <cstdlib>
#include <ctime>
#include <vector>
#include "pointsource.h"
#include "single_receiver.h"
#include "receivers_grid.h"



namespace  NoiseEngine
{    

    MATRIX_OF_DOUBLES createMatrixOfDoubles(unsigned int m, unsigned int n);
    void initSeed(); // initializes the seed only once
    int intRandom(int min, int max);

    void P2P(PointSource *pointSource, SingleReceiver *receiver);

    double distanceBetweenPoints(double x1, double y1, double z1,
                                 double x2, double y2, double z2);


    double sumdB(const double &Leq1, const double &Leq2);

    int greatestIntegerFunction(int x, int dx=100, int dy=25);

    void interpolationValueAt(
                            const double &t1,
                            const double &y1,
                            const double &t2,
                                  double &y2,
                            const double &t3,
                            const double &y3);


    void addRandomSources(vector<PointSource *> &pointSources, const GridSettings &myGrid);


};

#endif // DYNAMIC_MATRIX_H
