#include "qgraphics_polyline_source_item.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <math.h>
#include<QDebug>


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

    for(auto item: list){
        auto line_item = static_cast<QGraphicsLineItem *>(item);

//        path.addRect(item->boundingRect());
        path.addPolygon(getBufferOfLine(line_item));

    }

    return path;
}

void QGraphicsPolyLineSourceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::green);
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
    setCursor(Qt::PointingHandCursor);

    QGraphicsItem::hoverEnterEvent(event);
}

QPolygonF QGraphicsPolyLineSourceItem::getBufferOfLine(const QGraphicsLineItem *lineItem) const
{
    // this implementation of buffer zone is temporal, a better implementation
    // should include an algorithm as describe in the follow url:
    // https://www.boost.org/doc/libs/1_64_0/libs/geometry/doc/html/geometry/reference/algorithms/buffer/buffer_7_with_strategies.html
    // https://www.tandfonline.com/doi/full/10.1080/10095020.2012.747643
    QPolygonF polygon;
    double d = 10; // distance
    double PI = 3.141592;


//    double theta1 = lineItem->line().angle(QLine(0.0, 0.0, 1.0, 0.0));
    double theta1 = (180/PI)*atan( (lineItem->line().p2().y()-lineItem->line().p1().y())/(lineItem->line().p2().x()-lineItem->line().p1().x()) );

    QLineF line1;
    QLineF line2;

    if(theta1>=0 && theta1<90){
        line1 = lineItem->line().translated(10.0, -10.0);
        line2 = lineItem->line().translated(-10.0, 10.0);
    }else if(theta1<0 && theta1>-90){
        line1 = lineItem->line().translated(10.0, 10.0);
        line2 = lineItem->line().translated(-10.0, -10.0);
    }else{
        line1 = lineItem->line().translated(10.0, 0);
        line2 = lineItem->line().translated(-10.0, 0);
    }

    polygon<<line1.p1()<<line1.p2()<<line2.p2()<<line2.p1();
    return polygon;
}




MyQGraphicsLineItem::MyQGraphicsLineItem(QGraphicsItem *parent)
    : QGraphicsLineItem (parent)
{

}

MyQGraphicsLineItem::MyQGraphicsLineItem(const QLineF &line, QGraphicsItem *parent)
    : QGraphicsLineItem (line, parent)
{

}

void MyQGraphicsLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);

}
