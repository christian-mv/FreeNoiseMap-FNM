#ifndef POINTSOURCEPIXMAPITEM_H
#define POINTSOURCEPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class PointSource;


class PointSourcePixmapItem : public QGraphicsPixmapItem
{
public:
    PointSourcePixmapItem();
    void setPointSource(PointSource *source);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual int	type() const override;


private:
    PointSource *source;


protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);



};

#endif // ACOUSTICSOURCEPIXMAP_H
