#include "qgraphics_item_point_receiver.h"
#include "types_namespace.h"
#include "point_receiver.h"


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
