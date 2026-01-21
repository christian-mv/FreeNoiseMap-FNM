#include "polyline.h"

#include "types_namespace.h"
#include <QPainter>
#include <QDebug>

namespace fnm_ui {

PolyLine::PolyLine():
    AbstractPolyLine()
{

}

void PolyLine::addSegment(fnm_core::Segment *segment)
{
   // call protected superclass method
    AbstractPolyLine::addSegment(segment);
}

QVector<fnm_core::Segment *> *PolyLine::getSegments()
{
    return AbstractPolyLine::getSegments();
}


int PolyLine::type() const
{
    return fnm_core::TypeId::PolyLineItemType;
}

}
