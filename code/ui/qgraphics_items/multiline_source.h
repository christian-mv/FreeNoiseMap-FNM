#ifndef FNM_UI_QGRAPHICS_ITEM_MULTILINE_SOURCE_H
#define FNM_UI_QGRAPHICS_ITEM_MULTILINE_SOURCE_H

#include "abstract_polyline.h"

namespace fnm { class LineSourceSegment; }

namespace fnm {

class GraphicsItemMultiLineSource : public QgraphicsItemAbstractPolyLine
{
public:
    GraphicsItemMultiLineSource();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(fnm::LineSourceSegment *segment);
    QVector<fnm::LineSourceSegment*> getSegments();
    int	type() const override;

};

}
#endif // MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H