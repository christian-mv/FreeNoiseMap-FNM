#include "qgraphics_item_multiline_source.h"
#include "line_source_segment.h"
#include "types_namespace.h"
#include <QPainter>
#include <QDebug>


FnmGraphicsItemMultiLineSource::FnmGraphicsItemMultiLineSource():
    FnmQgraphicsItemAbstractPolyLine()
{

}

void FnmGraphicsItemMultiLineSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *w)
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

void FnmGraphicsItemMultiLineSource::addSegment(FnmLineSourceSegment *segment)
{
    FnmQgraphicsItemAbstractPolyLine::addSegment(segment);
}

QVector<FnmLineSourceSegment *> FnmGraphicsItemMultiLineSource::getSegments()
{
    QVector<FnmCore3DSegment*> *listSegments = FnmQgraphicsItemAbstractPolyLine::getSegments();
    QVector<FnmLineSourceSegment *> results;
    for(auto segment: *listSegments){
        results.append(static_cast<FnmLineSourceSegment *>(segment));
    }

    return results;
}



int FnmGraphicsItemMultiLineSource::type() const
{
    return FNM_TypeId::MultiLineSourceItemType;
}
