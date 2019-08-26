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
         const std::vector<MinimalAcousticBarrier*> &barrierSegments)
{
    double distance = distanceBetweenPoints(pointSource->get_x(),
                                            pointSource->get_y(),
                                            pointSource->get_z(),
                                            receiver->get_x(),
                                            receiver->get_y(),
                                            receiver->get_z());

    double A_div = attenuation_divergence(distance);

    double A_bar = 0;

    if(!barrierSegments.empty()){
        A_bar = attenuation_barrier(pointSource,receiver,barrierSegments, 500.0);
    }


    double Leq_result = pointSource->get_Lw() - A_div - A_bar;
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
    double dz = line->get_z2() - line->get_z1();
    double dw = line->get_Lw_total() - 10.0*log10(n); // Lw per point source

    for(int k=0; k<=n; k++){
        point.set_x( line->get_x1() + k*dx/n );
        point.set_y( line->get_y1() + k*dy/n );
        point.set_z( line->get_z1() + k*dz/n );
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
                           const std::vector<MinimalAcousticBarrier*> &barrierSegments,
                           const double &frequency)
{

    double  z, kmet, C2, C3, lambda, Dz;
    std::vector< std::tuple<double, double, double> > diffractionPath;

    diffractionPath =  calculateDiffractionPathPoints(pointSource->get_x(),
                                                pointSource->get_y(),
                                                pointSource->get_z(),
                                                receiver->get_x(),
                                                receiver->get_y(),
                                                receiver->get_z(),
                                                barrierSegments);

    if(diffractionPath.size()<=2){
        return 0;
    }

    BarrierPathdistances isoDistances;
    isoDistances = Iso9613BarrierDistances(diffractionPath);


    z = isoDistances.dss + isoDistances.dsr + isoDistances.e- isoDistances.d;

    // correct sign for z according to sightlight (pending)


//    z>0 ? kmet = std::pow( euler , -(1/2000)*std::sqrt(diffractionDistance*d/(2*z)) ) : kmet = 1;
    z>0 ? kmet = std::pow( euler , -(1/2000)*std::sqrt(isoDistances.dss*isoDistances.dsr*isoDistances.d/(2*z)) ) : kmet = 1;

    C2 = 20; // see ISO 9613
    C3 = 1; // single difraction
    // C3 for double difraction see equation 15 ISO 9613-2


    lambda = c/frequency;

    Dz = 10*std::log10( 3 + (C2/lambda)*C3*z*kmet );

    return Dz;
}


std::tuple<bool, double, double> intercectionBetween2DLineSegments(double p0x, double p0y,
                                                 double p1x, double p1y,
                                                 double p2x, double p2y,
                                                 double p3x, double p3y)
{
    // https://www.youtube.com/watch?v=4bIsntTiKfM&list=PL7wAPgl1JVvURU_YF4hHMcsWK98KbnZPs&index=2

    double intersectX, intersectY;
    double A1, B1, C1, A2, B2, C2, denominator;
    double rx0, ry0, rx1, ry1;

    A1 = p1y - p0y;
    B1 = p0x - p1x;
    C1 = A1 * p0x + B1 * p0y;
    A2 = p3y - p2y;
    B2 = p2x - p3x;
    C2 = A2 * p2x + B2 * p2y;
    denominator = A1*B2 - A2*B1;

    if(denominator == 0  || areTheseParallelLines(p0x, p0y,p1x, p1y,p2x, p2y,p3x, p3y)){
        return std::make_tuple(false, 0, 0);
    }

    intersectX = (B2*C1 - B1*C2)/denominator;
    intersectY = (A1*C2 - A2*C1)/denominator;

    rx0 = (intersectX - p0x) / (p1x - p0x);
    ry0 = (intersectY - p0y) / (p1y - p0y);
    rx1 = (intersectX - p2x) / (p3x - p2x);
    ry1 = (intersectY - p2y) / (p3y - p2y);

    if(((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) &&
            ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))) {
        return std::make_tuple(true, intersectX, intersectY);
    }
    else {
        return std::make_tuple(false, 0, 0);
    }

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

std::vector< std::tuple<double, double, double> > calculateDiffractionPathPoints(const double &x0, const double &y0, const double &z0,
                                                                           const double &x1, const double &y1, const double &z1,
                                                                           const std::vector<MinimalAcousticBarrier*> &barrierSegments)
{
    std::vector< std::tuple<double, double, double> > pathPoints;

    std::tuple<bool, double, double> intercection;
    pathPoints.push_back(std::make_tuple(x0,y0,z0));

    for(auto segment: barrierSegments){
        intercection = intercectionBetween2DLineSegments(x0,y0,x1,y1,
                                                         segment->get_x1(),
                                                         segment->get_y1(),
                                                         segment->get_x2(),
                                                         segment->get_y2());

        // take into account point that are positive intersections
        if(std::get<0>(intercection)){
            pathPoints.push_back(std::make_tuple(std::get<1>(intercection),
                                                std::get<2>(intercection),
                                                segment->get_height()));
        }
    }

    pathPoints.push_back(std::make_tuple(x1,y1,z1));

    // sort vector according to 2D distance from point x0,y0
    std::sort(pathPoints.begin(),
              pathPoints.end(),
              [&x0, &y0](const std::tuple<double, double, double> &a,
              const std::tuple<double, double, double> &b) -> bool{

        double aDistance = distanceBetweenPoints(x0,y0,0,
                                                 std::get<0>(a),
                                                 std::get<1>(a),0);

        double bDistance = distanceBetweenPoints(x0,y0,0,
                                                 std::get<0>(b),
                                                 std::get<1>(b),0);


        return aDistance < bDistance;
    });

    return pathPoints;
}


// for this function it is supposed that pathPoints is already sorted
BarrierPathdistances Iso9613BarrierDistances(const std::vector<std::tuple<double, double, double> > &pathPoints)
{

    BarrierPathdistances data;


    int lastIndex = pathPoints.size()-1;

    data.d = distanceBetweenPoints(std::get<0>(pathPoints.at(0)),
                                   std::get<1>(pathPoints.at(0)),
                                   std::get<2>(pathPoints.at(0)),

                                   std::get<0>(pathPoints.at(lastIndex)),
                                   std::get<1>(pathPoints.at(lastIndex)),
                                   std::get<2>(pathPoints.at(lastIndex)));


    data.dss = distanceBetweenPoints(std::get<0>(pathPoints.at(0)),
                                     std::get<1>(pathPoints.at(0)),
                                     std::get<2>(pathPoints.at(0)),

                                     std::get<0>(pathPoints.at(1)),
                                     std::get<1>(pathPoints.at(1)),
                                     std::get<2>(pathPoints.at(1)));



    data.dsr = distanceBetweenPoints(std::get<0>(pathPoints.at(lastIndex)),
                                     std::get<1>(pathPoints.at(lastIndex)),
                                     std::get<2>(pathPoints.at(lastIndex)),

                                     std::get<0>(pathPoints.at(lastIndex-1)),
                                     std::get<1>(pathPoints.at(lastIndex-1)),
                                     std::get<2>(pathPoints.at(lastIndex-1)));
    data.e = 0;

    for(int i= 1; i<=lastIndex-2; i++){
        data.e += distanceBetweenPoints(std::get<0>(pathPoints.at(i)),
                                        std::get<1>(pathPoints.at(i)),
                                        std::get<2>(pathPoints.at(i)),

                                        std::get<0>(pathPoints.at(i+1)),
                                        std::get<1>(pathPoints.at(i+1)),
                                        std::get<2>(pathPoints.at(i+1)));
    }


//    qDebug()<<"d: "<<data.d<<" dss: "<<data.dss<<" dsr: "<<data.dsr<<" e: "<<data.e;

    return data;

}



}; // end namespace


