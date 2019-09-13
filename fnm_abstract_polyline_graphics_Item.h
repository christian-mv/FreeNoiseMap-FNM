#ifndef FNMABSTRACTPOLYLINEGRAPHICSITEM_H
#define FNMABSTRACTPOLYLINEGRAPHICSITEM_H

#include <QGraphicsItem>
class Fnm3DSegment;


class FnmAbstractPolyLineGraphicsItem : public QGraphicsItem
{
public:
    FnmAbstractPolyLineGraphicsItem();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;


    void setBufferDistance(const double &newValue);

private:
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;

    void updateBoundingRectangle(Fnm3DSegment *newSegment);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void addSegment(Fnm3DSegment *segment);
    QVector<Fnm3DSegment*> * getSegments();
    QVector<Fnm3DSegment*> *lineSegmentsList;
};

#endif // FNMABSTRACTPOLYLINEGRAPHICSITEM_H
