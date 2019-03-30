#ifndef QGRAPHICS_POLYLINE_SOURCE_ITEM_H
#define QGRAPHICS_POLYLINE_SOURCE_ITEM_H

#include<QGraphicsItemGroup>
#include<QPolygonF>


class MyQGraphicsLineItem : public QGraphicsLineItem{
public:

    MyQGraphicsLineItem(const QLineF &line, QGraphicsItem *parent = nullptr);
    QPainterPath shape() const override;
    virtual int	type() const override;

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
private:
    qreal bufferDistance;
    void setBufferZoneDistance(const qreal & newValue);
};


class QGraphicsPolyLineSourceItem : public QGraphicsItemGroup{
public:
    QGraphicsPolyLineSourceItem(QGraphicsItem *parent = nullptr);
    void addLine(MyQGraphicsLineItem *lineItem);
    QPainterPath shape() const override;
    virtual int	type() const override;


protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    double Lw;

};



#endif // QGRAPHICS_POLYLINE_SOURCE_ITEM_H
