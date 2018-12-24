#include "qgraphics_polyline_source_item.h"

QGraphicsPolyLineSourceItem::QGraphicsPolyLineSourceItem()
    : Lw(-88)
{

}

void QGraphicsPolyLineSourceItem::addLine(QGraphicsLineItem *lineItem)
{
    qGraphicsLineItemsGroup.addToGroup(lineItem);
}

QGraphicsItemGroup *QGraphicsPolyLineSourceItem::getLinesGroup()
{
    return &qGraphicsLineItemsGroup;
}


