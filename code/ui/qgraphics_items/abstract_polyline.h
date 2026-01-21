#ifndef FNM_UI_QGRAPHICS_ITEM_ABSTRACT_POLYLINE_H
#define FNM_UI_QGRAPHICS_ITEM_ABSTRACT_POLYLINE_H

#include <QGraphicsItem>
namespace fnm { class Core3DSegment; }

namespace fnm {
// This is an abstract Class
class QgraphicsItemAbstractPolyLine : public QGraphicsItem
{
public:
    QgraphicsItemAbstractPolyLine();
    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;


    void setBufferDistance(const double &newValue);

private:
    double xMin, xMax, yMin, yMax; // this is intended to calculate bounding box
    double bufferDistance;

    void updateBoundingRectangle(fnm::Core3DSegment *newSegment);
    QPainterPath multilineBuffer; // this is return from shape()
    QPainterPath singleLineBuffer(QLineF line, const double &distance);
    void updateMultilineBuffer(QPainterPath newLineBuffer);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void addSegment(fnm::Core3DSegment *segment);
    QVector<fnm::Core3DSegment*> * getSegments();
    QVector<fnm::Core3DSegment*> *lineSegmentsList;
};
}
#endif // FNMABSTRACTPOLYLINEGRAPHICSITEM_H