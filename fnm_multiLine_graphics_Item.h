#ifndef FNM_POLYLINE_GRAPHICS_ITEM_H
#define FNM_POLYLINE_GRAPHICS_ITEM_H

#include "fnm_abstract_polyline_graphics_Item.h"
#include "fnm_3D_segment.h"


class FnmPolyLineGraphicsItem : public FnmAbstractPolyLineGraphicsItem
{
public:
    FnmPolyLineGraphicsItem();

    void addSegment(Fnm3DSegment *segment);
    QVector<Fnm3DSegment*> * getSegments();
    int	type() const override;    

};

#endif
