#ifndef FNM_UI_GRAPHICS_ITEM_POLYLINE_H
#define FNM_UI_GRAPHICS_ITEM_POLYLINE_H

#include "qgraphics_item_abstract_polyline.h"
#include "3D_segment.h"


class FnmQgraphicsItemPolyLine : public FnmQgraphicsItemAbstractPolyLine
{
public:
    FnmQgraphicsItemPolyLine();

    void addSegment(FnmCore3DSegment *segment);
    QVector<FnmCore3DSegment*> * getSegments();
    int	type() const override;    

};

#endif
