#include "noise_engine.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QtDebug>
using namespace std;

namespace  NoiseEngine
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


double distanceBetweenPoints(double x1, double y1, double z1, double x2, double y2, double z2)
{
    return sqrt( pow((x2-x1), 2) + pow((y2-y1), 2) + pow((z2-z1), 2));
}



void P2P(PointSource *pointSource, SingleReceiver *receiver)
{
    double distance = distanceBetweenPoints(pointSource->get_x(),
                                            pointSource->get_y(),
                                            pointSource->get_z(),
                                            receiver->get_x(),
                                            receiver->get_y(),
                                            receiver->get_z());
    double A_div;

    distance<1 ? A_div=0 : A_div = 20*std::log10(distance) + 11;

    double Leq_result = pointSource->get_Lw() - A_div;
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



void addRandomSources(vector<PointSource *> &pointSources, const GridSettings &myGrid)
{
    pointSources.push_back(new PointSource(100,100,0,90));
    pointSources.push_back(new PointSource(150,200,0,90));

    pointSources.push_back(new PointSource(20,50,0,80));

    //// random sources
    //    int nSources=3;
    //    int min_x = static_cast<int>(myGrid.getLeft());
    //    int max_x = static_cast<int>(myGrid.getRight());
    //    int min_y = static_cast<int>(myGrid.getTop());
    //    int max_y = static_cast<int>(myGrid.getBottom());
    //    int min_z = -5;
    //    int max_z = 5;
    //    qDebug()<<myGrid.getTop();

    //    for(int i=0; i<nSources; i++){
    //        pointSources.push_back(new PointSource(NoiseEngine::intRandom(min_x, max_x),
    //                                               NoiseEngine::intRandom(-min_y, -max_y),
    //                                               NoiseEngine::intRandom(min_z, max_z),
    //                                               NoiseEngine::intRandom(80, 85)));
    //    }
}

int greatestIntegerFunction(int x, int dx, int dy)
{
    /*
     * double greatestIntegerFunction(int x, int dx=100, int dy=25):
     *
     * NOTE 1: This function is documented in:
     * "James Stewwart; Lothar Redlin and Saleem Watson;
     * Precalculus, Mathematics for Calculus, 7th ed, section 2.2,
     *  - Greatest Integer Function"
     * The default values in the arguments (i.e. 100 and 25)
     * are arbitrary values that have been chosen in order to
     * reproduce an example of the book. (See example 6).
     *
     * NOTE 2: this function has been tested with positive numbers,
     *          it doesn't support negative values of x.
*/

    int lefLimit=0;
    int rightLimit=dx;
    int i = 0;

    while(true){
        if(x>lefLimit &&x<=rightLimit){
            return (i+1)*dy ; // return  f(x)=||x||
        }else{
           lefLimit = rightLimit;
           rightLimit+=dx;
           i++;

        }
    }
}

};


