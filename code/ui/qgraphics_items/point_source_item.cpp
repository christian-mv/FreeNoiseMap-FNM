#include "point_source_item.h"
#include "types_namespace.h"
#include "core/point_source.h"

namespace fnm_ui {

PointSourceItem::PointSourceItem():
    AbstractPointSourceItem()
{    

}

void PointSourceItem::setPointSource(fnm_core::PointSource *source)
{
    AbstractPointSourceItem::setPoint(source);
}

fnm_core::PointSource *PointSourceItem::getPointSource() const
{
    auto source  = AbstractPointSourceItem::getPoint();
    return static_cast<fnm_core::PointSource *>(source);
}


int PointSourceItem::type() const
{
    return fnm_core::TypeId::PointSourceItemType; // represents a custom item
}

}
