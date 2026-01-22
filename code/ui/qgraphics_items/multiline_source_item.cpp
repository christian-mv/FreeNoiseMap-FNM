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

    if(lineSegmentsList.empty()){
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

    for(const auto &segment : lineSegmentsList){

        point1.setX( segment->get_x1() );
        point1.setY( segment->get_y1() );

        point2.setX( segment->get_x2() );
        point2.setY( segment->get_y2() );

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

std::vector<fnm_core::LineSourceSegment *> MultiLineSourceItem::getSegments()
{
    std::vector<fnm_core::Segment*> listSegments = AbstractPolyLineItem::getSegments();
    std::vector<fnm_core::LineSourceSegment *> results;
    for(auto segment: listSegments){
        results.push_back(static_cast<fnm_core::LineSourceSegment *>(segment));
    }

    return results;
}



int MultiLineSourceItem::type() const
{
    return fnm_core::TypeId::MultiLineSourceItemType;
}

}
