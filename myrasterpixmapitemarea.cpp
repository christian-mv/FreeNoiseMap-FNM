#include "myrasterpixmapitemarea.h"
#include <QPainter>

MyRasterPixmapItemArea::MyRasterPixmapItemArea()
{

}

int MyRasterPixmapItemArea::type() const
{
    return 65536; // represents a custom item
}

void MyRasterPixmapItemArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

//    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(2);
    pen.setCosmetic(true); // line doesn't change when zoomming
    painter->setPen(pen);
    QRectF myMargin = boundingRect().adjusted(pen.width(), pen.width(), -pen.width(), -pen.width());
    painter->drawRect(myMargin);

}


