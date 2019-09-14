#ifndef FNM_QGRAPHICS_ITEM_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_POINT_SOURCE_H

#include <QGraphicsPixmapItem>

class FnmCorePointSource;


class FnmQgraphicsItemPointSource : public QGraphicsPixmapItem
{
public:
    FnmQgraphicsItemPointSource();
    void setPointSource(FnmCorePointSource *source);
    FnmCorePointSource * getPointSource()const;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual int	type() const override;


private:
    FnmCorePointSource *source;


protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);



};

#endif // ACOUSTICSOURCEPIXMAP_H
