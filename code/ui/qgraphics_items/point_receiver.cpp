#include "point_receiver.h"
#include "types_namespace.h"
#include "core/point_receiver.h"

namespace fnm_ui {

PointReceiver::PointReceiver():
    AbstractPointSource()
{    

}

void PointReceiver::setPointReceiver(fnm_core::CorePointReceiver *source)
{
    AbstractPointSource::setPoint(source);
}

fnm_core::CorePointReceiver *PointReceiver::getPointReceiver() const
{
    auto source  = AbstractPointSource::getPoint();
    return static_cast<fnm_core::CorePointReceiver *>(source);
}


int PointReceiver::type() const
{
    return fnm_core::TypeId::PointReceiverItemType; // represents a custom item
}

}
