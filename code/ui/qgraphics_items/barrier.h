#ifndef FNM_UI_QGRAPHICS_ITEM_BARRIER_H
#define FNM_UI_QGRAPHICS_ITEM_BARRIER_H


#include "abstract_polyline.h"

namespace fnm_core { class CoreBarrierSegment; }

namespace fnm_ui {

class Barrier : public AbstractPolyLine
{
public:
    Barrier();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(fnm_core::CoreBarrierSegment *segment);
    QVector<fnm_core::CoreBarrierSegment*> getSegments();
    int	type() const override;

};

}
#endif
