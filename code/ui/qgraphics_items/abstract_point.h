#ifndef FNM_QGRAPHICS_ITEM_ABSTRACT_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_ABSTRACT_POINT_SOURCE_H

#include <QGraphicsPixmapItem>

namespace fnm { class CorePoint; }

namespace fnm {

class QgraphicsItemAbstractPointSource : public QGraphicsPixmapItem
{
public:
    QgraphicsItemAbstractPointSource();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual int	type() const override = 0;

private:
    fnm::CorePoint *fnmCorePoint;

protected:
    void setPoint(fnm::CorePoint *fnmCorePoint);
    fnm::CorePoint * getPoint()const;

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

};

}
#endif