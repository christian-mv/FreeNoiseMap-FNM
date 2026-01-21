#include "qgraphics_item_point_source.h"
#include "types_namespace.h"
#include "point_source.h"


FnmQgraphicsItemPointSource::FnmQgraphicsItemPointSource():
    FnmQgraphicsItemAbstractPointSource()
{    

}

void FnmQgraphicsItemPointSource::setPointSource(FnmCorePointSource *source)
{
    FnmQgraphicsItemAbstractPointSource::setPoint(source);
}

FnmCorePointSource *FnmQgraphicsItemPointSource::getPointSource() const
{
    auto source  = FnmQgraphicsItemAbstractPointSource::getPoint();
    return static_cast<FnmCorePointSource *>(source);
}


int FnmQgraphicsItemPointSource::type() const
{
    return FNM_TypeId::PointSourceItemType; // represents a custom item
}
