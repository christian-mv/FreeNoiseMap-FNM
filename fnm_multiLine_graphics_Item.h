#ifndef FNM_MULTILINE_GRAPHICS_ITEM_H
#define FNM_MULTILINE_GRAPHICS_ITEM_H

#include <QGraphicsItem>
#include "fnm_3D_segment.h"


class FnmMultilineGraphicsItem : public QGraphicsItem
{
public:
    FnmMultilineGraphicsItem();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    int	type() const override;

    void addLineSource(Fnm3DSegment *lineSource);
    void addLineSource(const QLineF &line);
    QVector<Fnm3DSegment*> * getLineSources();
    void setBufferDistance(const double &newValue);


private:
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;
    QVector<Fnm3DSegment*> *lineSources;
    void updateBoundingRectangle(Fnm3DSegment *newSource);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // FNM_MULTILINE_GRAPHICS_ITEM_H
