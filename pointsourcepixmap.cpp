#include "pointsourcepixmapitem.h"

#include "pointsource.h"
#include <QDebug>

PointSourcePixmapItem::PointSourcePixmapItem()
{

}

void PointSourcePixmapItem::setPointSource(PointSource *source)
{
    this->source = source;

    this->prepareGeometryChange();
    this->setPos(source->get_x() - boundingRect().width()/2,
                 source->get_y() - boundingRect().height()/2);


}
