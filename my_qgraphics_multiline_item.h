#ifndef MY_QGRAPHICS_MULTILINE_ITEM_H
#define MY_QGRAPHICS_MULTILINE_ITEM_H

#include <QGraphicsItem>
#include <QLinkedList>
#include "minimal_line_source.h"


class MyQGraphicsMultiLineSource : public QGraphicsItem
{
public:
    MyQGraphicsMultiLineSource();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    int	type() const override;

    void addLineSource(const MinimalLineSource &lineSource);
    void addLineSource(const QLineF &line);
    const QVector<MinimalLineSource> * getLineSources();
    void setBufferDistance(const double &newValue);


private:
    QVector<MinimalLineSource> lineSources;
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    void updateBoundingRectangle(const MinimalLineSource &newSource);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);
    double bufferDistance;



};

#endif // MY_QGRAPHICS_MULTILINE_ITEM_H
