#include "point_receiver.h"
#include "types_namespace.h"
#include "core/point_receiver.h"

namespace fnm {

QgraphicsItemPointReceiver::QgraphicsItemPointReceiver():
    QgraphicsItemAbstractPointSource()
{    

}

void QgraphicsItemPointReceiver::setPointReceiver(fnm::CorePointReceiver *source)
{
    QgraphicsItemAbstractPointSource::setPoint(source);
}

fnm::CorePointReceiver *QgraphicsItemPointReceiver::getPointReceiver() const
{
    auto source  = QgraphicsItemAbstractPointSource::getPoint();
    return static_cast<fnm::CorePointReceiver *>(source);
}


int QgraphicsItemPointReceiver::type() const
{
    return fnm::TypeId::PointReceiverItemType; // represents a custom item
}

}