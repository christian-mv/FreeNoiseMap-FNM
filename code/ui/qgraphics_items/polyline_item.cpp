#include "polyline_item.h"

#include "types_namespace.h"
#include <QPainter>
#include <QDebug>

namespace fnm_ui {

PolyLineItem::PolyLineItem():
    AbstractPolyLineItem()
{

}

void PolyLineItem::addSegment(fnm_core::Segment *segment)
{
   // call protected superclass method
    AbstractPolyLineItem::addSegment(segment);
}

std::vector<fnm_core::Segment *> PolyLineItem::getSegments()
{
    return AbstractPolyLineItem::getSegments();
}


int PolyLineItem::type() const
{
    return fnm_core::TypeId::PolyLineItemType;
}

}
