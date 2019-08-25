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
        srand( static_cast<unsigned int>(time(nullptr)) );
        flagSeed = true; // now flag will be always true
    }
}


double distanceBetweenPoints(double x1, double y1, double z1, double x2, double y2, double z2)
{
    return sqrt( pow((x2-x1), 2) + pow((y2-y1), 2) + pow((z2-z1), 2));
}



void P2P(MinimalPointSource *pointSource,
         SingleReceiver *receiver,
         const Minimal_acoustic_barrier *barrier)
{
    double distance = distanceBetweenPoints(pointSource->get_x(),
                                            pointSource->get_y(),
                                            pointSource->get_z(),
                                            receiver->get_x(),
                                            receiver->get_y(),
                                            receiver->get_z());

    double A_div = attenuation_divergence(distance);





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


std::vector<MinimalPointSource> fromLineToPointSources(const MinimalLineSource *line,
                                                       const double &distanceBetweenPoints)
{
    std::vector<MinimalPointSource> results;
    MinimalPointSource point;
    int n = static_cast<int>(line->distance()/distanceBetweenPoints);
    double dx = line->get_x2() - line->get_x1();
    double dy = line->get_y2() - line->get_y1();
    double dw = line->get_Lw_total() - 10.0*log10(n); // Lw per point source

    for(int k=0; k<=n; k++){
        point.set_x( line->get_x1() + k*dx/n );
        point.set_y( line->get_y1() + k*dy/n );
        point.set_Lw(dw);
        results.push_back(point);
    }
    return results;
}

double attenuation_divergence(const double &distance)
{
    double A_div;
    distance<1 ? A_div=0 : A_div = 20*std::log10(distance) + 11;
    return A_div;
}

double attenuation_barrier(const MinimalPointSource* const pointSource,
                           const SingleReceiver* const receiver,
                           const Minimal_acoustic_barrier* const barrierSegment,
                           const double &frequency)
{


    bool parallel = areTheseParallelLines(pointSource->get_x(), pointSource->get_y(),
                                          receiver->get_x(), receiver->get_y(),
                                          barrierSegment->p1x, barrierSegment->p1y,
                                          barrierSegment->p2x, barrierSegment->p2y);
    if(parallel){
//        qDebug("Parallel lines");
        return 0.0;
    }

    std::tuple<double, double> intercetionPoint2D;
    intercetionPoint2D = intercectionPointBetween2DLines(pointSource->get_x(), pointSource->get_y(),
                                                     receiver->get_x(), receiver->get_y(),
                                                     barrierSegment->p1x, barrierSegment->p1y,
                                                     barrierSegment->p2x, barrierSegment->p2y);



    double dss, dsr, d, z, kmet, C2, C3, lambda, Dz;

    dss = distanceBetweenPoints(pointSource->get_x(),
                                pointSource->get_y(),
                                pointSource->get_z(),
                                std::get<0>(intercetionPoint2D),
                                std::get<1>(intercetionPoint2D),
                                barrierSegment->height);


    dsr = distanceBetweenPoints(receiver->get_x(),
                                receiver->get_y(),
                                receiver->get_z(),
                                std::get<0>(intercetionPoint2D),
                                std::get<1>(intercetionPoint2D),
                                barrierSegment->height);

    d = distanceBetweenPoints(pointSource->get_x(),
                              pointSource->get_y(),
                              pointSource->get_z(),
                              receiver->get_x(),
                              receiver->get_y(),
                              receiver->get_z());


    z = dss + dsr - d;

    // correct sign for z according to sightlight (pending)


    z>0 ? kmet = std::pow( euler , -(1/2000)*std::sqrt(dss*dsr*d/(2*z)) ) : kmet = 1;

    C2 = 20; // see ISO 9613
    C3 = 1; // single difraction
    // C3 for double difraction see equation 15 ISO 9613-2


    lambda = c/frequency;

    Dz = 10*std::log10( 3 + (C2/lambda)*C3*z*kmet );

    return Dz;
}

std::tuple<double, double> intercectionPointBetween2DLines(double p0x, double p0y,
                                                 double p1x, double p1y,
                                                 double p2x, double p2y,
                                                 double p3x, double p3y)
{
    // https://www.youtube.com/watch?v=4bIsntTiKfM

    double x_result, y_result;
    double A1, B1, C1, A2, B2, C2, denominator;

    A1 = p1y - p0y;
    B1 = p0x - p1x;
    C1 = A1 * p0x + B1 * p0y;
    A2 = p3y - p2y;
    B2 = p2x - p3x;
    C2 = A2 * p2x + B2 * p2y;
    denominator = A1*B2 - A2*B1;

    x_result = (B2*C1 - B1*C2)/denominator;
    y_result = (A1*C2 - A2*C1)/denominator;

    return std::make_tuple(x_result, y_result);
}

bool areTheseParallelLines(double p0x, double p0y, double p1x, double p1y,
                           double p2x, double p2y, double p3x, double p3y)
{
    // Precalculus 7Ed, chapter 1; James Stewart
    double m1, m2;
    m1 = (p1y - p0y)/(p1x - p0x);
    m2 = (p3y - p2y)/(p3x - p2x);
    return (m1 == m2);
}

}; // end namespace


