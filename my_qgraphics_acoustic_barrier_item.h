#ifndef MY_QGRAPHICS_ACOUSTIC_BARRIER_ITEM_H
#define MY_QGRAPHICS_ACOUSTIC_BARRIER_ITEM_H


#include "fnm_abstract_polyline_graphics_Item.h"

class FnmAcousticBarrierSegment;


class MyQGraphicsAcousticBarrierItem : public FnmAbstractPolyLineGraphicsItem
{
public:
    MyQGraphicsAcousticBarrierItem();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(FnmAcousticBarrierSegment *segment);
    QVector<FnmAcousticBarrierSegment*> getSegments();
    int	type() const override;

};


#endif
