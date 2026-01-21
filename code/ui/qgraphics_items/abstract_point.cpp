#include "abstract_point.h"
#include <QCursor>
#include "point.h"
#include <QRectF>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

namespace fnm_ui {

AbstractPointSource::AbstractPointSource()
{    
    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void AbstractPointSource::setPoint(fnm::CorePoint *source)
{
    this->fnmCorePoint = source;

    prepareGeometryChange();

    setPos(source->get_x(), source->get_y() );

    // when applying ItemIgnoresTransformations flag to prevent the father to
    // scale the item, the position of the item becomes wrong. This problem
    // is fixed accordint to "Game Prgramming Using Qt 5, Beginner's Guide, 2ED"
    // chapter 4, page 121, Time for action - Adding text to a custom rectangle"
    // https://books.google.com.au/books?id=kPBZDwAAQBAJ&pg=PA122&lpg=PA122&dq=ItemIgnoresTransformations+position&source=bl&ots=0gXQwFS5sJ&sig=jgayweVbC_EK3XKQbixE4_IYfeI&hl=en&sa=X&ved=2ahUKEwi-x6K-xvPdAhVKZt4KHVK8CO4Q6AEwDHoECAIQAQ#v=onepage&q=ItemIgnoresTransformations%20position&f=false
    QTransform transform;
    transform.translate(-QGraphicsPixmapItem::boundingRect().width()/2, -QGraphicsPixmapItem::boundingRect().height()/2);
    this->setTransform(transform);
}

fnm::CorePoint *AbstractPointSource::getPoint() const
{
    return fnmCorePoint;
}



QRectF AbstractPointSource::boundingRect() const
{

    // if the app is running in a mobile or tablet,
    // we enlarge the selection area of the item to enhance
    // the user interaction in touch screens

    #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    return QGraphicsPixmapItem::boundingRect().adjusted(-50, -50, 50, 50);
    #else
    return QGraphicsPixmapItem::boundingRect();
    #endif

}

// reimplamenting shape to guarantee that the selection area is enlarged
// this is applying for android and IOS devices.
QPainterPath AbstractPointSource::shape() const
{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}



void AbstractPointSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isSelected()){
        QPen pen(Qt::black);
        pen.setWidth(1);
        painter->setPen(pen);
        QRectF myMargin = QGraphicsPixmapItem::boundingRect();
        painter->drawRect(myMargin);
        // Avoid superclass painting rectangle when selected (SEE: https://stackoverflow.com/questions/10985028/how-to-remove-border-around-qgraphicsitem-when-selected)
        QStyleOptionGraphicsItem myOption(*option);
        myOption.state &= ~QStyle::State_Selected;
        QGraphicsPixmapItem::paint(painter, &myOption, widget);
    }else{
        QGraphicsPixmapItem::paint(painter, option, widget);
    }
}

QVariant AbstractPointSource::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionChange &&  scene() ) {        
        // value is the new position.
        QPointF newPos = value.toPointF();
        fnmCorePoint->set_x(newPos.x());
        fnmCorePoint->set_y(newPos.y());
    }

    return QGraphicsItem::itemChange(change, value);
}

void AbstractPointSource::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

}