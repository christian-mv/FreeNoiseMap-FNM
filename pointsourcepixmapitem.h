#ifndef POINTSOURCEPIXMAPITEM_H
#define POINTSOURCEPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class PointSource;


class PointSourcePixmapItem : public QGraphicsPixmapItem
{
public:
    PointSourcePixmapItem();
    void setPointSource(PointSource *source);
    QRectF boundingRect() const;
    QPainterPath shape() const;


private:
    PointSource *source;


protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);



};

#endif // ACOUSTICSOURCEPIXMAP_H
