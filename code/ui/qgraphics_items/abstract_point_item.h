#ifndef FNM_QGRAPHICS_ITEM_ABSTRACT_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_ABSTRACT_POINT_SOURCE_H

#include <QGraphicsPixmapItem>

namespace fnm_core { class Point; }

namespace fnm_ui {

class AbstractPointSourceItem : public QGraphicsPixmapItem
{
public:
    AbstractPointSourceItem();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;

private:
    fnm_core::Point *fnmCorePoint;

protected:
    void setPoint(fnm_core::Point *fnmCorePoint);
    fnm_core::Point * getPoint()const;

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

};

}
#endif
