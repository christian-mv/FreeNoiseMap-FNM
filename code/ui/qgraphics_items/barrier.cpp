#include "barrier.h"
#include "barrier_segment.h"
#include "types_namespace.h"
#include <QPainter>
#include <QDebug>

namespace fnm_ui {

Barrier::Barrier():
    AbstractPolyLine()
{

}

void Barrier::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *w)
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

void Barrier::addSegment(fnm::CoreBarrierSegment *segment)
{
    AbstractPolyLine::addSegment(segment);
}

QVector<fnm::CoreBarrierSegment *> Barrier::getSegments()
{
    QVector<fnm::Core3DSegment*> *listSegments = AbstractPolyLine::getSegments();
    QVector<fnm::CoreBarrierSegment *> results;
    for(auto segment: *listSegments){
        results.append(static_cast<fnm::CoreBarrierSegment *>(segment));
    }

    return results;
}



int Barrier::type() const
{
    return fnm::TypeId::AcousticBarrierItemType;
}

}