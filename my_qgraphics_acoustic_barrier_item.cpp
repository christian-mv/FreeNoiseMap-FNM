#include "my_qgraphics_acoustic_barrier_item.h"
#include "fnm_acoustic_barrier_segment.h"
#include "fnm_types.h"
#include <QPainter>
#include <QDebug>

MyQGraphicsAcousticBarrierItem::MyQGraphicsAcousticBarrierItem():
    FnmAbstractPolyLineGraphicsItem()
{

}

void MyQGraphicsAcousticBarrierItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *w)
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

void MyQGraphicsAcousticBarrierItem::addSegment(FnmAcousticBarrierSegment *segment)
{
    FnmAbstractPolyLineGraphicsItem::addSegment(segment);
}

QVector<FnmAcousticBarrierSegment *> MyQGraphicsAcousticBarrierItem::getSegments()
{
    QVector<Fnm3DSegment*> *listSegments = FnmAbstractPolyLineGraphicsItem::getSegments();
    QVector<FnmAcousticBarrierSegment *> results;
    for(auto segment: *listSegments){
        results.append(static_cast<FnmAcousticBarrierSegment *>(segment));
    }

    return results;
}



int MyQGraphicsAcousticBarrierItem::type() const
{
    return FNM_TypeId::AcousticBarrierItemType;
}

