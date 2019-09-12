#ifndef MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H
#define MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H

#include <QGraphicsItem>
#include "fnm_line_segment_source.h"


class MyQGraphicsMultiLineSource : public QGraphicsItem
{
public:
    MyQGraphicsMultiLineSource();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    int	type() const override;

    void addLineSource(FnmLineSegmentSource *lineSource);
    void addLineSource(const QLineF &line, double Lw_total);
    QVector<FnmLineSegmentSource*> * getLineSources();
    void setBufferDistance(const double &newValue);


private:    
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;
    QVector<FnmLineSegmentSource*> *lineSources;
    void updateBoundingRectangle(FnmLineSegmentSource *newSource);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H
