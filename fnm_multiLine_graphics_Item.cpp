#include "fnm_multiLine_graphics_Item.h"

#include "fnm_types.h"
#include <QPainter>
#include <QDebug>


FnmPolyLineGraphicsItem::FnmPolyLineGraphicsItem():
    FnmAbstractPolyLineGraphicsItem()
{

}

void FnmPolyLineGraphicsItem::addSegment(Fnm3DSegment *segment)
{
   // call protected superclass method
   FnmAbstractPolyLineGraphicsItem::addSegment(segment);
}


int FnmPolyLineGraphicsItem::type() const
{
    return FNM_TypeId::PolyLineItemType;
}
