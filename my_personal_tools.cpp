#include "my_personal_tools.h"
#include <cstdlib>
#include <ctime>

namespace  MyPersonalTools
{
    MATRIX_OF_DOUBLES createMatrixOfDoubles(unsigned int m, unsigned int n){
        MATRIX_OF_DOUBLES myMatriz;

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
        initSeed(); // this guarantees that seed has been initialized at least once
        int result;        
        result = min + rand() % ( (max+1) - min );
        return result;
    }

    void initSeed()
    {
        static bool flagSeed=false;
        if(!flagSeed){
            srand(time(nullptr));
            flagSeed = true; // now flag will be always true
        }
    }


};


