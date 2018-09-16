#include "widget.h"
#include <QApplication>
#include "noise_engine.h"
#include <QtDebug>
#include <QScrollArea>
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



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    GridSettings myGrid;
    ReceiversGrid receivers;
    vector<PointSource *> pointSources;




    myGrid.setRect(QRectF(50, 50, 200, 200));
    myGrid.setDeltaX(1);
    myGrid.setDeltaY(1);
    myGrid.setInterpolationFactor(5);
    receivers.setGrid(myGrid);

    addRandomSources(pointSources, myGrid);



    NoiseEngine::calculateNoiseFromSources(&pointSources, &receivers);



    qreal side = qMin(myGrid.getRect().width(), myGrid.getRect().height());
    qreal side2 = qMax(w.width(), w.height());




    QImage image(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);

    image.fill(Qt::transparent);

    receivers.paintGrid(image, myGrid);


    image.save("../test.png", "PNG");

    w.setImage(&image);

    w.show();
    return a.exec();

}




