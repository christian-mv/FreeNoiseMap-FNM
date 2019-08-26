#ifndef MY_QGRAPHICS_ACOUSTIC_BARRIER_ITEM_H
#define MY_QGRAPHICS_ACOUSTIC_BARRIER_ITEM_H

#include <QGraphicsItem>
#include "minimal_acoustic_barrier.h"

class MyQGraphicsAcousticBarrierItem : public QGraphicsItem
{
public:
    MyQGraphicsAcousticBarrierItem();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    int	type() const override;

    void addBarrierSegment(MinimalAcousticBarrier *lineSource);
    void addBarrierSegment(const QLineF &line, double height);
    QVector<MinimalAcousticBarrier*> getBarrierSegments();
    void setBufferDistance(const double &newValue);


private:
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;
    QVector<MinimalAcousticBarrier*> barrierSegments;
    void updateBoundingRectangle(MinimalAcousticBarrier *newBarrierSegment);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // MY_QGRAPHICS_ACOUSTIC_BARRIER_ITEM_H
