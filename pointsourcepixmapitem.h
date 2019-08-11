#ifndef POINTSOURCEPIXMAPITEM_H
#define POINTSOURCEPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class MinimalPointSource;


class PointSourcePixmapItem : public QGraphicsPixmapItem
{
public:
    PointSourcePixmapItem();
    void setPointSource(MinimalPointSource *source);
    MinimalPointSource * getPointSource()const;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual int	type() const override;


private:
    MinimalPointSource *source;


protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);



};

#endif // ACOUSTICSOURCEPIXMAP_H
