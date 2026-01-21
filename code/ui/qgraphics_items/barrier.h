#ifndef FNM_UI_QGRAPHICS_ITEM_BARRIER_H
#define FNM_UI_QGRAPHICS_ITEM_BARRIER_H


#include "abstract_polyline.h"

namespace fnm_core { class BarrierSegment; }

namespace fnm_ui {

class Barrier : public AbstractPolyLine
{
public:
    Barrier();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(fnm_core::BarrierSegment *segment);
    QVector<fnm_core::BarrierSegment*> getSegments();
    int	type() const override;

};

}
#endif
