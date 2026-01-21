#ifndef FNM_UI_GRAPHICS_ITEM_POLYLINE_H
#define FNM_UI_GRAPHICS_ITEM_POLYLINE_H

#include "abstract_polyline_item.h"
#include "segment.h"

namespace fnm_ui {

class PolyLineItem : public AbstractPolyLineItem
{
public:
    PolyLineItem();

    void addSegment(fnm_core::Segment *segment);
    QVector<fnm_core::Segment*> * getSegments();
    int	type() const override;    

};

}
#endif
