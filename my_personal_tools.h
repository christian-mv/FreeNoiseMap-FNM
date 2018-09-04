#ifndef MY_PERSONAL_TOOLS_H
#define MY_PERSONAL_TOOLS_H

#define MATRIX_OF_DOUBLES std::vector< std::vector<double> >

#include <cstdlib>
#include <ctime>
#include <vector>


namespace  MyPersonalTools
{
    MATRIX_OF_DOUBLES createMatrixOfDoubles(unsigned int m, unsigned int n);
    void initSeed(); // initializes the seed only once
    int intRandom(int min, int max);
};

#endif // DYNAMIC_MATRIX_H
