#include "fnm_multiLine_graphics_Item.h"

#include "fnm_types.h"
#include <QPainter>
#include <QDebug>


FnmMultilineGraphicsItem::FnmMultilineGraphicsItem():
    xMin(0), xMax(0), yMin(0), yMax(0), bufferDistance(10.0),
    lineSegmentsList(new QVector<Fnm3DSegment*>)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QRectF FnmMultilineGraphicsItem::boundingRect() const
{
//    QRectF rect( xMin, yMin, qAbs(xMax-xMin), qAbs(yMax-yMin) );
//    return rect.adjusted(-10,-10,10,10);
    return this->multilineBuffer.boundingRect();
}

void FnmMultilineGraphicsItem::paint(QPainter *painter,
                                       const QStyleOptionGraphicsItem *opt,
                                       QWidget *w)
{
    Q_UNUSED(opt)
    Q_UNUSED(w)

    if(lineSegmentsList->length()<1){
        return;
    }

    QPen pen(Qt::black);
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
//    pen.setColor(Qt::darkGray);
//    pen.setStyle(Qt::PenStyle::SolidLine);
//    painter->setPen(pen);
//    painter->drawPath(shape());

}

QPainterPath FnmMultilineGraphicsItem::shape() const
{
    /*
     * this implementation take into accout the buffer distance
     * source: https://stackoverflow.com/questions/5730409/qpainterpath-grow-expand
     * an alternative implementations for the buffer zone can be found in:
     *
     * https://www.boost.org/doc/libs/1_64_0/libs/geometry/doc/html/geometry/reference/algorithms/buffer/buffer_7_with_strategies.html
     *
     * https://www.tandfonline.com/doi/full/10.1080/10095020.2012.747643
     *
     * https://stackoverflow.com/questions/2667748/how-do-i-combine-complex-polygons
     *
    */
//   QPainterPath oldPath = multilineBuffer;
//   QPainterPathStroker stroker;
//   stroker.setWidth(10);
//   stroker.setJoinStyle(Qt::MiterJoin); // and other adjustments you need
//   QPainterPath newpath = (stroker.createStroke(oldPath) + oldPath).simplified();
//   return newpath;

    return multilineBuffer;
}

int FnmMultilineGraphicsItem::type() const
{
    return FNM_TypeId::PolyLineItemType;
}

void FnmMultilineGraphicsItem::addLineSegment(Fnm3DSegment *segment)
{
    prepareGeometryChange();
    QPainterPath newSegmentBuffer = singleLineBuffer(QLineF(segment->get_x1(),
                                                         segment->get_y1(),
                                                         segment->get_x2(),
                                                         segment->get_y2()), bufferDistance);

    // init some values when the first line is inserted
    if(lineSegmentsList->size()<1){
        multilineBuffer = newSegmentBuffer;
        xMin = qMin(segment->get_x1(), segment->get_x2());
        yMin = qMin(segment->get_y1(), segment->get_y2());

        xMax = qMax(segment->get_x1(), segment->get_x2());
        yMax = qMax(segment->get_y1(), segment->get_y2());
    }

    // update multilineBufferZone
    if(lineSegmentsList->size()>=1) {
        updateMultilineBuffer(newSegmentBuffer);
    }

    lineSegmentsList->append(segment);

    updateBoundingRectangle(segment);

}

void FnmMultilineGraphicsItem::addLineSegment(const QLineF &line)
{
    Fnm3DSegment *source = new Fnm3DSegment();
    source->set_p1(line.x1(), line.y1(), 0);
    source->set_p2(line.x2(), line.y2(), 0);
    addLineSegment(source);
}

QVector<Fnm3DSegment*> *FnmMultilineGraphicsItem::getLineSegments()
{
    return lineSegmentsList;
}

void FnmMultilineGraphicsItem::setBufferDistance(const double &newValue)
{
    bufferDistance = newValue;
}




void FnmMultilineGraphicsItem::updateBoundingRectangle(Fnm3DSegment *newSegment)
{
    double temp;

    // updating xMin
    newSegment->get_x1()<=newSegment->get_x2() ? temp=newSegment->get_x1() : temp=newSegment->get_x2();

    if(temp<xMin){
        xMin = temp;
    }

    // updating xMax
    newSegment->get_x1()>=newSegment->get_x2() ? temp=newSegment->get_x1() : temp=newSegment->get_x2();
    if(temp>xMax){
        xMax = temp;
    }

    // updating yMin
    newSegment->get_y1()<=newSegment->get_y2() ? temp=newSegment->get_y1() : temp=newSegment->get_y2();
    if(temp<yMin){
        yMin = temp;
    }

    // updating yMax
    newSegment->get_y1()>=newSegment->get_y2() ? temp=newSegment->get_y1() : temp=newSegment->get_y2();
    if(temp>yMax){
        yMax = temp;
    }

}

QPainterPath FnmMultilineGraphicsItem::singleLineBuffer(QLineF line, const double &distance)
{
    QPainterPath temp;
    temp.moveTo(line.p1());
    temp.lineTo(line.p2());

    QPainterPathStroker stroker;
    stroker.setWidth(distance);
    stroker.setJoinStyle(Qt::MiterJoin); // and other adjustments you need
    QPainterPath newpath = (stroker.createStroke(temp) + temp).simplified();
    return newpath;
}

void FnmMultilineGraphicsItem::updateMultilineBuffer(QPainterPath newLineBuffer)
{
    multilineBuffer = multilineBuffer.united(newLineBuffer);
}

QVariant FnmMultilineGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange &&  scene() ) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        double dx = newPos.x() - pos().x();
        double dy = newPos.y()  - pos().y();

        for(auto segment: *lineSegmentsList){
            segment->moveBy(dx, dy, 0);
        }

    }
    return QGraphicsItem::itemChange(change, value);
}



