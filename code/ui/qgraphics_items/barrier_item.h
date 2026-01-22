#ifndef FNM_UI_QGRAPHICS_ITEM_BARRIER_H
#define FNM_UI_QGRAPHICS_ITEM_BARRIER_H


#include "abstract_polyline_item.h"
#include <vector>

namespace fnm_core { class BarrierSegment; }

namespace fnm_ui {

class BarrierItem : public AbstractPolyLineItem
{
public:
    BarrierItem();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(fnm_core::BarrierSegment *segment);
    std::vector<fnm_core::BarrierSegment*> getSegments();
    int	type() const override;

};

}
#endif
