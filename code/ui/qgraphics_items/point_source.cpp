#include "point_source.h"
#include "types_namespace.h"
#include "core/point_source.h"

namespace fnm {

PointSource::PointSource():
    AbstractPointSource()
{    

}

void PointSource::setPointSource(fnm::CorePointSource *source)
{
    AbstractPointSource::setPoint(source);
}

fnm::CorePointSource *PointSource::getPointSource() const
{
    auto source  = AbstractPointSource::getPoint();
    return static_cast<fnm::CorePointSource *>(source);
}


int PointSource::type() const
{
    return fnm::TypeId::PointSourceItemType; // represents a custom item
}

}