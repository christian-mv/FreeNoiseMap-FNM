#include "my_personal_tools.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <QtDebug>
using namespace std;

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


    double distanceBetweenPoints(double x1, double y1, double z1, double x2, double y2, double z2)
    {
        return sqrt( pow((x2-x1), 2) + pow((y2-y1), 2) + pow((z2-z1), 2));
    }

    void calculateNoiseFromSources(const vector<PointSource *> *sources,
                                   ReceiversGrid *receivers )
    {
        for(auto row : receivers->matrix){
            for(auto currentReceiver : row){
                for(auto currentSource : *sources){
                    P2P(currentSource, currentReceiver);
                }
            }
        }
    }

    void P2P(PointSource *pointSource, SingleReceiver *receiver)
    {
        double distance = distanceBetweenPoints(pointSource->get_x(),
                                                pointSource->get_y(),
                                                pointSource->get_z(),
                                                receiver->get_x(),
                                                receiver->get_y(),
                                                receiver->get_z());

        double A_div = 20*std::log10(distance) + 11;

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

};


