#include "polyline.h"

#include "types_namespace.h"
#include <QPainter>
#include <QDebug>


FnmQgraphicsItemPolyLine::FnmQgraphicsItemPolyLine():
    FnmQgraphicsItemAbstractPolyLine()
{

}

void FnmQgraphicsItemPolyLine::addSegment(FnmCore3DSegment *segment)
{
   // call protected superclass method
    FnmQgraphicsItemAbstractPolyLine::addSegment(segment);
}

QVector<FnmCore3DSegment *> *FnmQgraphicsItemPolyLine::getSegments()
{
    return FnmQgraphicsItemAbstractPolyLine::getSegments();
}


int FnmQgraphicsItemPolyLine::type() const
{
    return FNM_TypeId::PolyLineItemType;
}
