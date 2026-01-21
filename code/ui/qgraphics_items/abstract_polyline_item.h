#ifndef FNM_UI_QGRAPHICS_ITEM_ABSTRACT_POLYLINE_H
#define FNM_UI_QGRAPHICS_ITEM_ABSTRACT_POLYLINE_H

#include <QGraphicsItem>
namespace fnm_core { class Segment; }

namespace fnm_ui {
// This is an abstract Class
class AbstractPolyLineItem : public QGraphicsItem
{
public:
    AbstractPolyLineItem();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;


    void setBufferDistance(const double &newValue);

private:
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;

    void updateBoundingRectangle(fnm_core::Segment *newSegment);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void addSegment(fnm_core::Segment *segment);
    QVector<fnm_core::Segment*> * getSegments();
    QVector<fnm_core::Segment*> *lineSegmentsList;
};
}
#endif // FNMABSTRACTPOLYLINEGRAPHICSITEM_H
