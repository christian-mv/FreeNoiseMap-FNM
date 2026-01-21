#ifndef FNM_QGRAPHICS_ITEM_ABSTRACT_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_ABSTRACT_POINT_SOURCE_H

#include <QGraphicsPixmapItem>

class FnmCorePoint;

class FnmQgraphicsItemAbstractPointSource : public QGraphicsPixmapItem
{
public:
    FnmQgraphicsItemAbstractPointSource();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;

private:
    FnmCorePoint *fnmCorePoint;

protected:
    void setPoint(FnmCorePoint *fnmCorePoint);
    FnmCorePoint * getPoint()const;

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

};

#endif
