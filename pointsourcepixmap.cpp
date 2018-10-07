#include "pointsourcepixmapitem.h"

#include "pointsource.h"
#include <QRectF>
#include <QDebug>
#include <QPainter>
#include <QPen>


PointSourcePixmapItem::PointSourcePixmapItem()
{

}

void PointSourcePixmapItem::setPointSource(PointSource *source)
{
    this->source = source;

    prepareGeometryChange();
    setPos(source->get_x() - boundingRect().width()/2,
                 source->get_y() - boundingRect().height()/2);

//    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

}



void PointSourcePixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);
    QRectF myMargin = boundingRect().adjusted(10, 10, -10, -10);
    painter->drawRect(myMargin);
    painter->restore();
    QGraphicsPixmapItem::paint(painter, option, widget);
}


