#include "polyline.h"

#include "types_namespace.h"
#include <QPainter>
#include <QDebug>

namespace fnm {

QgraphicsItemPolyLine::QgraphicsItemPolyLine():
    QgraphicsItemAbstractPolyLine()
{

}

void QgraphicsItemPolyLine::addSegment(fnm::Core3DSegment *segment)
{
   // call protected superclass method
    QgraphicsItemAbstractPolyLine::addSegment(segment);
}

QVector<fnm::Core3DSegment *> *QgraphicsItemPolyLine::getSegments()
{
    return QgraphicsItemAbstractPolyLine::getSegments();
}


int QgraphicsItemPolyLine::type() const
{
    return fnm::TypeId::PolyLineItemType;
}

}