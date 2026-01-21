#include "point_source.h"
#include "types_namespace.h"
#include "core/point_source.h"

namespace fnm_ui {

PointSource::PointSource():
    AbstractPointSource()
{    

}

void PointSource::setPointSource(fnm_core::CorePointSource *source)
{
    AbstractPointSource::setPoint(source);
}

fnm_core::CorePointSource *PointSource::getPointSource() const
{
    auto source  = AbstractPointSource::getPoint();
    return static_cast<fnm_core::CorePointSource *>(source);
}


int PointSource::type() const
{
    return fnm_core::TypeId::PointSourceItemType; // represents a custom item
}

}
