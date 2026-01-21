#ifndef FNM_UI_QGRAPHICS_ITEM_MULTILINE_SOURCE_H
#define FNM_UI_QGRAPHICS_ITEM_MULTILINE_SOURCE_H

#include "abstract_polyline_item.h"

namespace fnm_core { class LineSourceSegment; }

namespace fnm_ui {

class MultiLineSourceItem : public AbstractPolyLineItem
{
public:
    MultiLineSourceItem();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(fnm_core::LineSourceSegment *segment);
    QVector<fnm_core::LineSourceSegment*> getSegments();
    int	type() const override;

};

}
#endif // MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H
