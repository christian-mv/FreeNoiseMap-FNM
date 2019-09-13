#ifndef MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H
#define MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H

#include "fnm_abstract_polyline_graphics_Item.h"

class FnmLineSegmentSource;


class MyQGraphicsMultiLineSource : public FnmAbstractPolyLineGraphicsItem
{
public:
    MyQGraphicsMultiLineSource();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) override;
    void addSegment(FnmLineSegmentSource *segment);
    QVector<FnmLineSegmentSource*> getSegments();
    int	type() const override;

};

#endif // MY_QGRAPHICS_MULTILINE_SOURCE_ITEM_H
