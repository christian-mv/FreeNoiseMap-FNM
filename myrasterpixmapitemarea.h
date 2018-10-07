#ifndef MYRASTERPIXMAPITEMAREA_H
#define MYRASTERPIXMAPITEMAREA_H
#include <QGraphicsPixmapItem>

class QPainter;

class MyRasterPixmapItemArea : public QGraphicsPixmapItem
{
public:
    MyRasterPixmapItemArea();
    virtual int	type() const override;


};

#endif // MYRASTERPIXMAPITEMAREA_H
