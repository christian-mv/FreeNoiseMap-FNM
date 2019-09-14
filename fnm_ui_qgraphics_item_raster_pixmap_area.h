#ifndef FNM_UI_QGRAPHICS_ITEM_RASTER_PIXMAP_AREA_H
#define FNM_UI_QGRAPHICS_ITEM_RASTER_PIXMAP_AREA_H
#include <QGraphicsPixmapItem>

class QPainter;

class FnmQgraphicsItemRasterPixmap : public QGraphicsPixmapItem
{
public:
    FnmQgraphicsItemRasterPixmap();
    virtual int	type() const override;


    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;



};

#endif // MYRASTERPIXMAPITEMAREA_H
