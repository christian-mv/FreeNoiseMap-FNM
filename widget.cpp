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

    setAttribute(Qt::WA_StaticContents); // avoid painting when resizing window
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    myGrid.setRect(QRectF(-100, -100, 200, 200));
    myGrid.setDeltaX(0.3);
    myGrid.setDeltaY(0.3);
    receivers.setGrid(myGrid);;
    pointSources.clear();
    pointSources.push_back(new PointSource(0,0,0,85));

//    // adding random sources:
//    int nSources=3;
//    int min_x = static_cast<int>(myGrid.getLeft());
//    int max_x = static_cast<int>(myGrid.getRight());
//    int min_y = static_cast<int>(myGrid.getBottom());
//    int max_y = static_cast<int>(myGrid.getTop());
//    int min_z = -5;
//    int max_z = 5;

//    for(int i=0; i<nSources; i++){
//        pointSources.push_back(new PointSource(MyPersonalTools::intRandom(min_x, max_x),
//                                               MyPersonalTools::intRandom(-min_y, -max_y),
//                                               MyPersonalTools::intRandom(min_z, max_z),
//                                               MyPersonalTools::intRandom(80, 86)));
//    }

    MyPersonalTools::calculateNoiseFromSources(&pointSources, &receivers);
    paintRasterOnQimage(&painter,1);


    image->save("../test.png", "PNG");
//    this->update();
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    this->drawMargin();



}

void Widget::paintRasterOnQimage(QPainter *painter, int zoom)
{
    painter->translate(this->myGrid.getRect().center());

    qreal side = qMin(painter->device()->width(), painter->device()->height());

    painter->scale(zoom*side/width(), -zoom*side/height());


    receivers.paintGrid(painter);
}


void Widget::drawNoiseCell(QPainter *painter, QColor color, QRectF rect)
{
    painter->setBrush(color);
    painter->drawRect(rect);
}


void Widget::drawMargin(int dx1, int dy1, int dx2, int dy2)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    QRectF myMargin = rect().adjusted(dx1, dy1, -dx2, -dy2);
    painter.drawRect(myMargin);



//    qreal side = qMin(width(), height());

//    painter.scale(side/width(), side/height());

    painter.drawImage(rect(),*image,image->rect());
}



