#include "widget.h"
#include <QPainter>
#include <QRegion>
#include <QPaintEvent>
#include "my_personal_tools.h"
#include <QRectF>
#include <QtWidgets>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    image = new QImage(rect().size(), QImage::Format_ARGB32);

    image->fill(Qt::transparent);
    QPainter painter(image);

    myGrid.setRect(QRectF(50, 20, 220, 220));
    myGrid.setDeltaX(1);
    myGrid.setDeltaY(1);
    myGrid.setInterpolationFactor(5);
    receivers.setGrid(myGrid);;


    pointSources.push_back(new PointSource(100,100,0,90));



//    int nSources=2;
//    int min_x = static_cast<int>(myGrid.getLeft());
//    int max_x = static_cast<int>(myGrid.getRight());
//    int min_y = static_cast<int>(myGrid.getTop());
//    int max_y = static_cast<int>(myGrid.getBottom());
//    int min_z = -5;
//    int max_z = 5;
//    qDebug()<<myGrid.getTop();

//    for(int i=0; i<nSources; i++){
//        pointSources.push_back(new PointSource(MyPersonalTools::intRandom(min_x, max_x),
//                                               MyPersonalTools::intRandom(-min_y, -max_y),
//                                               MyPersonalTools::intRandom(min_z, max_z),
//                                               MyPersonalTools::intRandom(80, 85)));
//    }

    MyPersonalTools::calculateNoiseFromSources(&pointSources, &receivers);
    paintRasterOnQimage(&painter,0.8);


    image->save("../test.png", "PNG");
//    this->update();
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    this->drawMargin();

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(rect(),*image,image->rect());
}

void Widget::paintRasterOnQimage(QPainter *painter, double zoom)
{
    if(zoom<0.1){
        zoom=0.1; // limit the zoomm to positive values greater than 0.1
    }
    painter->translate(this->myGrid.getRect().bottomLeft());

    qreal side = qMin(painter->device()->width(), painter->device()->height());

    painter->scale(zoom*side/width(), -zoom*side/height());


    receivers.paintGrid(painter);
}
