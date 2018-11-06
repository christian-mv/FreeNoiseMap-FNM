#include "mainwindow.h"
#include <QApplication>
#include "noise_engine.h"
#include <QtDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include "gradientcolor.h"

void addRandomSources(vector<PointSource *> &pointSources, const GridSettings &myGrid)
{
    pointSources.push_back(new PointSource(100,100,0,90));
    pointSources.push_back(new PointSource(150,150,0,90));

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


#include<iostream>
using namespace std;

double greatestIntegerFunction(int x, int dx=100, int dy=25){

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
            cout<<"\ni: "<<i<<endl;
            return (i+1)*dy ; // return  f(x)=||x||
        }else{
           lefLimit = rightLimit;
           rightLimit+=dx;
           i++;

        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.showMaximized();
    return a.exec();
}




