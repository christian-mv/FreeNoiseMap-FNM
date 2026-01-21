#ifndef FNM_UI_QGRAPHICS_ITEM_MULTILINE_SOURCE_H
#define FNM_UI_QGRAPHICS_ITEM_MULTILINE_SOURCE_H

#include "abstract_polyline.h"

class FnmLineSourceSegment;

class FnmGraphicsItemMultiLineSource : public FnmQgraphicsItemAbstractPolyLine
{
public:
    FnmGraphicsItemMultiLineSource();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(FnmLineSourceSegment *segment);
    QVector<FnmLineSourceSegment*> getSegments();
    int	type() const override;

};

#endif // MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H
