#ifndef FNM_UI_QGRAPHICS_ITEM_BARRIER_H
#define FNM_UI_QGRAPHICS_ITEM_BARRIER_H


#include "abstract_polyline.h"

namespace fnm { class CoreBarrierSegment; }

namespace fnm {

class QGraphicsItemBarrier : public QgraphicsItemAbstractPolyLine
{
public:
    QGraphicsItemBarrier();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(fnm::CoreBarrierSegment *segment);
    QVector<fnm::CoreBarrierSegment*> getSegments();
    int	type() const override;

};

}
#endif