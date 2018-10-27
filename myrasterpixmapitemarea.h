#ifndef MYRASTERPIXMAPITEMAREA_H
#define MYRASTERPIXMAPITEMAREA_H
#include <QGraphicsPixmapItem>

class QPainter;

class MyRasterPixmapItemArea : public QGraphicsPixmapItem
{
public:
    MyRasterPixmapItemArea();
    virtual int	type() const override;


    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;



};

#endif // MYRASTERPIXMAPITEMAREA_H
