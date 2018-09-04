#include "dynamic_matrix.h"

namespace  DynamicMatrix
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
};


