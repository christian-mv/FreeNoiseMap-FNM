#include "qgraphics_polyline_source_item.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <math.h>
#include <QDebug>
#include "fnm_types.h"
#include <QPainterPathStroker>
#include <QGraphicsSceneHoverEvent>


QGraphicsPolyLineSourceItem::QGraphicsPolyLineSourceItem(QGraphicsItem *parent)
    :QGraphicsItemGroup(parent ),Lw(-88.0)
{

}

void QGraphicsPolyLineSourceItem::addLine(MyQGraphicsLineItem *lineItem)
{
    addToGroup(lineItem);
}

QPainterPath QGraphicsPolyLineSourceItem::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QList<QGraphicsItem *> list = QGraphicsItem::childItems();
    QPolygonF tempPolygon;

    for(auto item: list){
        auto line_item = static_cast<QGraphicsLineItem *>(item);

//        path.addPolygon(getBufferOfLine(line_item)); // this is intended of custom buffers

        tempPolygon = line_item->shape().toFillPolygon();
        path.addPolygon(tempPolygon);

    }

    return path;
}

int QGraphicsPolyLineSourceItem::type() const
{
    return FNM_TypeId::LineSourceItemType;
}

void QGraphicsPolyLineSourceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::green);
    pen.setCosmetic(true); // line doesn't change when zoomming
    pen.setWidth(1);
    painter->setPen(pen);
//        QRectF myMargin = QGraphicsLineItem::boundingRect();
//        painter->drawRect(myMargin);
    QPainterPath path  = shape();
    painter->drawPath(path);
    // Avoid superclass painting rectangle when selected (SEE: https://stackoverflow.com/questions/10985028/how-to-remove-border-around-qgraphicsitem-when-selected)
    QStyleOptionGraphicsItem myOption(*option);
    myOption.state &= ~QStyle::State_Selected;
    QGraphicsItemGroup::paint(painter, &myOption, widget);
}

void QGraphicsPolyLineSourceItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    setCursor(Qt::PointingHandCursor);

    QList<QGraphicsItem *> list = QGraphicsItem::childItems();
    for(auto item: list){
        auto line_item = static_cast<QGraphicsItem *>(item);
        line_item->setCursor(Qt::PointingHandCursor);
    }
    event->accept();


//    QGraphicsItemGroup::hoverEnterEvent(event);
}


MyQGraphicsLineItem::MyQGraphicsLineItem(const QLineF &line, QGraphicsItem *parent)
    : QGraphicsLineItem (line, parent)
{
    setBufferZoneDistance(10.0);
}

QPainterPath MyQGraphicsLineItem::shape() const
{
     /*
      * this implementation take into accout the buffer distance
      * source: https://stackoverflow.com/questions/5730409/qpainterpath-grow-expand
      * an alternative implementation for the buffer zone can be found in:
      * https://www.boost.org/doc/libs/1_64_0/libs/geometry/doc/html/geometry/reference/algorithms/buffer/buffer_7_with_strategies.htmlhttps://www.tandfonline.com/doi/full/10.1080/10095020.2012.747643
     */
    QPainterPath oldPath = QGraphicsLineItem::shape();
    QPainterPathStroker stroker;
    stroker.setWidth(this->bufferDistance);
    stroker.setJoinStyle(Qt::MiterJoin); // and other adjustments you need
    QPainterPath newpath = (stroker.createStroke(oldPath) + oldPath).simplified();
    return newpath;
}



void MyQGraphicsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::blue);
    painter->setPen(pen);
    pen.setCosmetic(true); // line doesn't change when zoomming
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawLine(this->line());
    //    QGraphicsLineItem::paint(painter,option,widget);
}

void MyQGraphicsLineItem::setBufferZoneDistance(const qreal &newValue)
{
    bufferDistance = newValue;
}

