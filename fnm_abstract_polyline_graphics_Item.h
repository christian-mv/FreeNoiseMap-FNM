#ifndef FNMABSTRACTPOLYLINEGRAPHICSITEM_H
#define FNMABSTRACTPOLYLINEGRAPHICSITEM_H

#include <QGraphicsItem>
#include "fnm_3D_segment.h"

class FnmAbstractPolyLineGraphicsItem : public QGraphicsItem
{
public:
    FnmAbstractPolyLineGraphicsItem();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;

    QVector<Fnm3DSegment*> * getSegments();
    void setBufferDistance(const double &newValue);

private:
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;
    QVector<Fnm3DSegment*> *lineSegmentsList;
    void updateBoundingRectangle(Fnm3DSegment *newSegment);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void addSegment(Fnm3DSegment *segment);
};

#endif // FNMABSTRACTPOLYLINEGRAPHICSITEM_H
