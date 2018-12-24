#ifndef QGRAPHICS_POLYLINE_SOURCE_ITEM_H
#define QGRAPHICS_POLYLINE_SOURCE_ITEM_H

#include<QGraphicsItemGroup>
class QGraphicsLineItem;

class QGraphicsPolyLineSourceItem
{
public:
    QGraphicsPolyLineSourceItem();
    void addLine(QGraphicsLineItem *lineItem);
    QGraphicsItemGroup * getLinesGroup();


private:
    QGraphicsItemGroup qGraphicsLineItemsGroup;
    double Lw; // total sound power level
};

#endif // QGRAPHICS_POLYLINE_SOURCE_ITEM_H
