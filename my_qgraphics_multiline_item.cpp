#include "my_qgraphics_multiline_item.h"
#include "fnm_types.h"
#include <QPainter>



MyQGraphicsMultiLineSource::MyQGraphicsMultiLineSource():
    xMin(0), xMax(0), yMin(0), yMax(0), bufferDistance(10.0)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QRectF MyQGraphicsMultiLineSource::boundingRect() const
{
//    QRectF rect( xMin, yMin, qAbs(xMax-xMin), qAbs(yMax-yMin) );
//    return rect.adjusted(-10,-10,10,10);
    return this->multilineBuffer.boundingRect();
}

void MyQGraphicsMultiLineSource::paint(QPainter *painter,
                                       const QStyleOptionGraphicsItem *opt,
                                       QWidget *w)
{
    Q_UNUSED(opt)
    Q_UNUSED(w)

    if(lineSources.length()<1){
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

    for(int i=0; i<lineSources.length(); i++){

        point1.setX( lineSources.at(i).get_x1() );
        point1.setY( lineSources.at(i).get_y1() );

        point2.setX( lineSources.at(i).get_x2() );
        point2.setY( lineSources.at(i).get_y2() );

        painter->drawLine(point1, point2);
    }
    pen.setColor(Qt::green);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter->setPen(pen);
//    painter->drawRect(boundingRect());
    painter->drawPath(shape());

}

QPainterPath MyQGraphicsMultiLineSource::shape() const
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

int MyQGraphicsMultiLineSource::type() const
{
    return FNM_TypeId::MultiLineSourceItemType;
}

void MyQGraphicsMultiLineSource::addLineSource(const MinimalLineSource &newSource)
{
    prepareGeometryChange();
    QPainterPath newSegmentBuffer = singleLineBuffer(QLineF(newSource.get_x1(),
                                                         newSource.get_y1(),
                                                         newSource.get_x2(),
                                                         newSource.get_y2()), bufferDistance);

    // init some values when the first line is inserted
    if(lineSources.size()<1){
        multilineBuffer = newSegmentBuffer;

        xMin = qMin(newSource.get_x1(), newSource.get_x2());
        yMin = qMin(newSource.get_y1(), newSource.get_y2());

        xMax = qMax(newSource.get_x1(), newSource.get_x2());
        yMax = qMax(newSource.get_y1(), newSource.get_y2());
    }

    // update multilineBufferZone
    if(lineSources.size()>=1) {
        updateMultilineBuffer(newSegmentBuffer);
    }

    lineSources.append(newSource);

    updateBoundingRectangle(newSource);

}

void MyQGraphicsMultiLineSource::addLineSource(const QLineF &line)
{
    MinimalLineSource source;
    source.set_p1(line.x1(), line.y1(), 0);
    source.set_p2(line.x2(), line.y2(), 0);
    addLineSource(source);
}

const QVector<MinimalLineSource> *MyQGraphicsMultiLineSource::getLineSources()
{
    return &lineSources;
}

void MyQGraphicsMultiLineSource::setBufferDistance(const double &newValue)
{
    bufferDistance = newValue;
}


void MyQGraphicsMultiLineSource::updateBoundingRectangle(const MinimalLineSource &newSource)
{
    double temp;

    // updating xMin
    newSource.get_x1()<=newSource.get_x2() ? temp=newSource.get_x1() : temp=newSource.get_x2();

    if(temp<xMin){
        xMin = temp;
    }

    // updating xMax
    newSource.get_x1()>=newSource.get_x2() ? temp=newSource.get_x1() : temp=newSource.get_x2();
    if(temp>xMax){
        xMax = temp;
    }

    // updating yMin
    newSource.get_y1()<=newSource.get_y2() ? temp=newSource.get_y1() : temp=newSource.get_y2();
    if(temp<yMin){
        yMin = temp;
    }

    // updating yMax
    newSource.get_y1()>=newSource.get_y2() ? temp=newSource.get_y1() : temp=newSource.get_y2();
    if(temp>yMax){
        yMax = temp;
    }

}

QPainterPath MyQGraphicsMultiLineSource::singleLineBuffer(QLineF line, const double &distance)
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

void MyQGraphicsMultiLineSource::updateMultilineBuffer(QPainterPath newLineBuffer)
{
    multilineBuffer = multilineBuffer.united(newLineBuffer);
}


