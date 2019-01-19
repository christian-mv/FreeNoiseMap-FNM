#ifndef QGRAPHICS_POLYLINE_SOURCE_ITEM_H
#define QGRAPHICS_POLYLINE_SOURCE_ITEM_H

#include<QGraphicsItemGroup>
#include<QPolygonF>


class MyQGraphicsLineItem : public QGraphicsLineItem{
public:
    MyQGraphicsLineItem(QGraphicsItem *parent = nullptr);
    MyQGraphicsLineItem(const QLineF &line, QGraphicsItem *parent = nullptr);

protected:
    void  hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
};


class QGraphicsPolyLineSourceItem : public QGraphicsItemGroup{
public:
    QGraphicsPolyLineSourceItem(QGraphicsItem *parent = nullptr);
    void addLine(MyQGraphicsLineItem *lineItem);
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    double Lw;
    QPolygonF getBufferOfLine(const QGraphicsLineItem *line) const;


};



#endif // QGRAPHICS_POLYLINE_SOURCE_ITEM_H
