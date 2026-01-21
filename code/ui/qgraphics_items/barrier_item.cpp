#include "barrier_item.h"
#include "barrier_segment.h"
#include "types_namespace.h"
#include <QPainter>
#include <QDebug>

namespace fnm_ui {

BarrierItem::BarrierItem():
    AbstractPolyLineItem()
{

}

void BarrierItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    Q_UNUSED(opt)
    Q_UNUSED(w)

    if(lineSegmentsList->length()<1){
        return;
    }

    // draw filled path
       QBrush brush;
       painter->setRenderHint(QPainter::Antialiasing);
       brush.setColor(Qt::darkGray);
       brush.setStyle(Qt::SolidPattern);
       painter->fillPath(shape(),brush);


//    QPointF point1;
//    QPointF point2;

//    for(int i=0; i<lineSegmentsList->length(); i++){

//        point1.setX( lineSegmentsList->at(i)->get_x1() );
//        point1.setY( lineSegmentsList->at(i)->get_y1() );

//        point2.setX( lineSegmentsList->at(i)->get_x2() );
//        point2.setY( lineSegmentsList->at(i)->get_y2() );

//        // it is neccesary to substract pos() to compesate
//        // when the line source has been moved
//        painter->drawLine(point1-pos(), point2-pos());
//    }
//    // draw Rectangle
//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::PenStyle::SolidLine);
//    painter->setPen(pen);
//    painter->drawRect(boundingRect());

//    // draw buffer zone
//    pen.setColor(Qt::darkGray);
//    pen.setStyle(Qt::PenStyle::SolidLine);
//    painter->setPen(pen);
//    painter->drawPath(shape());
}

void BarrierItem::addSegment(fnm_core::BarrierSegment *segment)
{
    AbstractPolyLineItem::addSegment(segment);
}

QVector<fnm_core::BarrierSegment *> BarrierItem::getSegments()
{
    QVector<fnm_core::Segment*> *listSegments = AbstractPolyLineItem::getSegments();
    QVector<fnm_core::BarrierSegment *> results;
    for(auto segment: *listSegments){
        results.append(static_cast<fnm_core::BarrierSegment *>(segment));
    }

    return results;
}



int BarrierItem::type() const
{
    return fnm_core::TypeId::AcousticBarrierItemType;
}

}
