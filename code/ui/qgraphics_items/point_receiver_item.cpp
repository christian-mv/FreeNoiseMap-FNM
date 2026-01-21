#include "point_receiver_item.h"
#include "types_namespace.h"
#include "core/point_receiver.h"

namespace fnm_ui {

PointReceiverItem::PointReceiverItem():
    AbstractPointSourceItem()
{    

}

void PointReceiverItem::setPointReceiver(fnm_core::PointReceiver *source)
{
    AbstractPointSourceItem::setPoint(source);
}

fnm_core::PointReceiver *PointReceiverItem::getPointReceiver() const
{
    auto source  = AbstractPointSourceItem::getPoint();
    return static_cast<fnm_core::PointReceiver *>(source);
}


int PointReceiverItem::type() const
{
    return fnm_core::TypeId::PointReceiverItemType; // represents a custom item
}

}
