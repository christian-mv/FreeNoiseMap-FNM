#include "point_source.h"
#include "types_namespace.h"
#include "core/point_source.h"

namespace fnm {

QgraphicsItemPointSource::QgraphicsItemPointSource():
    QgraphicsItemAbstractPointSource()
{    

}

void QgraphicsItemPointSource::setPointSource(fnm::CorePointSource *source)
{
    QgraphicsItemAbstractPointSource::setPoint(source);
}

fnm::CorePointSource *QgraphicsItemPointSource::getPointSource() const
{
    auto source  = QgraphicsItemAbstractPointSource::getPoint();
    return static_cast<fnm::CorePointSource *>(source);
}


int QgraphicsItemPointSource::type() const
{
    return fnm::TypeId::PointSourceItemType; // represents a custom item
}

}