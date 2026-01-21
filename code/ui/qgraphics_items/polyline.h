#ifndef FNM_UI_GRAPHICS_ITEM_POLYLINE_H
#define FNM_UI_GRAPHICS_ITEM_POLYLINE_H

#include "abstract_polyline.h"
#include "3D_segment.h"

namespace fnm {

class PolyLine : public AbstractPolyLine
{
public:
    PolyLine();

    void addSegment(fnm::Core3DSegment *segment);
    QVector<fnm::Core3DSegment*> * getSegments();
    int	type() const override;    

};

}
#endif