#include "my_qgraphics_multiline_source_item.h"
#include "fnm_line_segment_source.h"
#include "fnm_types.h"
#include <QPainter>
#include <QDebug>


MyQGraphicsMultiLineSource::MyQGraphicsMultiLineSource():
    FnmAbstractPolyLineGraphicsItem()
{

}

void MyQGraphicsMultiLineSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *w)
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

void MyQGraphicsMultiLineSource::addSegment(FnmLineSegmentSource *segment)
{
    FnmAbstractPolyLineGraphicsItem::addSegment(segment);
}

QVector<FnmLineSegmentSource *> MyQGraphicsMultiLineSource::getSegments()
{
    QVector<Fnm3DSegment*> *listSegments = FnmAbstractPolyLineGraphicsItem::getSegments();
    QVector<FnmLineSegmentSource *> results;
    for(auto segment: *listSegments){
        results.append(static_cast<FnmLineSegmentSource *>(segment));
    }

    return results;
}



int MyQGraphicsMultiLineSource::type() const
{
    return FNM_TypeId::MultiLineSourceItemType;
}
