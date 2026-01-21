#include "fnm_ui_qgraphics_item_point_receiver.h"
#include "fnm_core_types_namespace.h"
#include "fnm_core_point_receiver.h"


FnmQgraphicsItemPointReceiver::FnmQgraphicsItemPointReceiver():
    FnmQgraphicsItemAbstractPointSource()
{    

}

void FnmQgraphicsItemPointReceiver::setPointReceiver(FnmCorePointReceiver *source)
{
    FnmQgraphicsItemAbstractPointSource::setPoint(source);
}

FnmCorePointReceiver *FnmQgraphicsItemPointReceiver::getPointReceiver() const
{
    auto source  = FnmQgraphicsItemAbstractPointSource::getPoint();
    return static_cast<FnmCorePointReceiver *>(source);
}


int FnmQgraphicsItemPointReceiver::type() const
{
    return FNM_TypeId::PointReceiverItemType; // represents a custom item
}
