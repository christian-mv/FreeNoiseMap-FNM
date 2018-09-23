#ifndef POINTSOURCEPIXMAPITEM_H
#define POINTSOURCEPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class PointSource;

class PointSourcePixmapItem : public QGraphicsPixmapItem
{
public:
    PointSourcePixmapItem();
    void setPointSource(PointSource *source);

private:
    PointSource *source;


};

#endif // ACOUSTICSOURCEPIXMAP_H
