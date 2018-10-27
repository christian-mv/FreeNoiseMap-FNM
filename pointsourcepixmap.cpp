#include "pointsourcepixmapitem.h"

#include "pointsource.h"
#include <QRectF>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


PointSourcePixmapItem::PointSourcePixmapItem()
{
    // avoid to scale the item
    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void PointSourcePixmapItem::setPointSource(PointSource *source)
{
    this->source = source;

    prepareGeometryChange();

    setPos(source->get_x(), source->get_y() );

    // when applying ItemIgnoresTransformations flag to prevent the father to
    // scale the item, the position of the item becomes wrong. This problem
    // is fixed accordint to "Game Prgramming Using Qt 5, Beginner's Guide, 2ED"
    // chapter 4, page 121, Time for action - Adding text to a custom rectangle"
    // https://books.google.com.au/books?id=kPBZDwAAQBAJ&pg=PA122&lpg=PA122&dq=ItemIgnoresTransformations+position&source=bl&ots=0gXQwFS5sJ&sig=jgayweVbC_EK3XKQbixE4_IYfeI&hl=en&sa=X&ved=2ahUKEwi-x6K-xvPdAhVKZt4KHVK8CO4Q6AEwDHoECAIQAQ#v=onepage&q=ItemIgnoresTransformations%20position&f=false
    QTransform transform;
    transform.translate(-boundingRect().width()/2, -boundingRect().height()/2);
    this->setTransform(transform);
}



void PointSourcePixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    // paint a rectangle wrapping the item
//    painter->save();
//    QPen pen(Qt::black);
//    pen.setWidth(1);
//    painter->setPen(pen);
//    QRectF myMargin = boundingRect().adjusted(1, 1, -1, -1);
//    painter->drawRect(myMargin);
//    painter->restore();

    QGraphicsPixmapItem::paint(painter, option, widget);
}

QVariant PointSourcePixmapItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionChange &&  scene() ) {

        // value is the new position.
        QPointF newPos = value.toPointF();
//        if(newPos.x() != source->get_x() && newPos.y() != source->get_y()){
            source->set_x(newPos.x());
            source->set_y(newPos.y());

//        }



    }

    return QGraphicsItem::itemChange(change, value);
}

