#include "fnm_ui_qgraphics_item_raster_pixmap_area.h"
#include "fnm_core_types_namespace.h"
#include <QPainter>


FnmQgraphicsItemRasterPixmap::FnmQgraphicsItemRasterPixmap()
{
    setAcceptHoverEvents(true);
}

int FnmQgraphicsItemRasterPixmap::type() const
{
    return FNM_TypeId::RasterPixmapItemType; // represents a custom item
}

void FnmQgraphicsItemRasterPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

//    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(2);
    pen.setCosmetic(true); // line doesn't change when zoomming
    painter->setPen(pen);
    QRectF myMargin = boundingRect().adjusted(pen.width(), pen.width(), -pen.width(), -pen.width());
    painter->drawRect(myMargin);

}




