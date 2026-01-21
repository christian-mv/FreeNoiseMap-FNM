#ifndef FNM_UI_QGRAPHICS_ITEM_BARRIER_H
#define FNM_UI_QGRAPHICS_ITEM_BARRIER_H


#include "abstract_polyline.h"

class FnmCoreBarrierSegment;


class FnmQGraphicsItemBarrier : public FnmQgraphicsItemAbstractPolyLine
{
public:
    FnmQGraphicsItemBarrier();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(FnmCoreBarrierSegment *segment);
    QVector<FnmCoreBarrierSegment*> getSegments();
    int	type() const override;

};


#endif
