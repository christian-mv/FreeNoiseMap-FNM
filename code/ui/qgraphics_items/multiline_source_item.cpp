#include "multiline_source_item.h"
#include "line_source_segment.h"
#include "types_namespace.h"
#include <QPainter>
#include <QDebug>

namespace fnm_ui {

MultiLineSourceItem::MultiLineSourceItem():
    AbstractPolyLineItem()
{

}

void MultiLineSourceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    Q_UNUSED(opt)
    Q_UNUSED(w)

    if(lineSegmentsList->length()<1){
        return;
    }

    QPen pen(Qt::blue);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    pen.setCosmetic(true); // line doesn't change when zoomming
    pen.setWidth(1);
    painter->setPen(pen);


    QPointF point1;
    QPointF point2;

    for(int i=0; i<lineSegmentsList->length(); i++){

        point1.setX( lineSegmentsList->at(i)->get_x1() );
        point1.setY( lineSegmentsList->at(i)->get_y1() );

        point2.setX( lineSegmentsList->at(i)->get_x2() );
        point2.setY( lineSegmentsList->at(i)->get_y2() );

        // it is neccesary to substract pos() to compesate
        // when the line source has been moved
        painter->drawLine(point1-pos(), point2-pos());
    }
//    // draw Rectangle
//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::PenStyle::SolidLine);
//    painter->setPen(pen);
//    painter->drawRect(boundingRect());

    // draw buffer zone
    pen.setColor(Qt::darkGray);
    pen.setStyle(Qt::PenStyle::SolidLine);
    painter->setPen(pen);
    painter->drawPath(shape());
}

void MultiLineSourceItem::addSegment(fnm_core::LineSourceSegment *segment)
{
    AbstractPolyLineItem::addSegment(segment);
}

QVector<fnm_core::LineSourceSegment *> MultiLineSourceItem::getSegments()
{
    QVector<fnm_core::Segment*> *listSegments = AbstractPolyLineItem::getSegments();
    QVector<fnm_core::LineSourceSegment *> results;
    for(auto segment: *listSegments){
        results.append(static_cast<fnm_core::LineSourceSegment *>(segment));
    }

    return results;
}



int MultiLineSourceItem::type() const
{
    return fnm_core::TypeId::MultiLineSourceItemType;
}

}
