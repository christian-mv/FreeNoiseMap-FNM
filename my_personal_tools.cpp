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

    void interpolateGrid(ReceiversGrid *receivers)
    {

        unsigned int factor = receivers->getGridSettings().getInterpolatorFactor();
        if(factor<=1){return;}

        SingleReceiver interpolatedReceiver;
        SingleReceiver *r;
        vector<SingleReceiver *> temprow;
        vector<vector<SingleReceiver *>> tempMatrix; // esto es una matriz intermedia de receptores

        double dx = receivers->getGridSettings().getDeltaX()/factor;
        double dy = receivers->getGridSettings().getDeltaY()/factor;
        double Leqx_temp; // here store interpolated Leq on x axes.
        double Leqy_temp; // here store interpolated Leq on y axes.

        //  interpolated rectangles on x axes
        for(int i = 0; i<receivers->matrix.size(); i++){
            for(int j = 0; j<receivers->matrix.at(i).size(); j=j+factor){

                r = receivers->matrix.at(i).at(j);
                if(j<receivers->matrix.at(i).size()-1){
                    for(int k=1; k<factor; k++){

                        MyPersonalTools::interpolationValueAt(r->get_x(),
                                                              r->get_Leq(),
                                                              r->get_x()+k*dx,
                                                              Leqx_temp,
                                                              receivers->matrix.at(i).at(j+1)->get_x(),
                                                              receivers->matrix.at(i).at(j+1)->get_Leq());


                        receivers->matrix.at(i).insert(receivers->matrix.at(i).begin()+j+1,
                                                       new SingleReceiver(r->get_x()+k*dx,
                                                                          r->get_y(),
                                                                          r->get_z(),
                                                                          Leqx_temp,true));
                    } // for k
                }// if
            } // for j
        } // for i




        // interpolated rectangles on y axes

        std::vector<SingleReceiver *> centinel = receivers->matrix.back();

        for(int i = 0; ; i=i+factor){

            if(receivers->matrix.at(i) == centinel) // beak when the last row is reached
            {
                break;
            }
                for(int k=1; k<factor; k++){
                    for(int j = 0; j<receivers->matrix.at(i).size(); j++){

                        r = receivers->matrix.at(i).at(j);

                        MyPersonalTools::interpolationValueAt(r->get_y(),
                                                              r->get_Leq(),
                                                              r->get_y()+k*dy,
                                                              Leqy_temp,
                                                              receivers->matrix.at(i+1).at(j)->get_y(),
                                                              receivers->matrix.at(i+1).at(j)->get_Leq());


                        temprow.push_back(new SingleReceiver(r->get_x(),
                                                             r->get_y()+k*dy,
                                                             r->get_z(),
                                                             Leqy_temp,true));

                    } // for: k

                    tempMatrix.push_back(temprow);
                    temprow.clear();

                }//
                receivers->matrix.insert(receivers->matrix.begin()+i,tempMatrix.begin(), tempMatrix.end());
                tempMatrix.clear();
        } //
    }
};


