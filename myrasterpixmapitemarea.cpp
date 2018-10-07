#include "myrasterpixmapitemarea.h"
#include <QPainter>

MyRasterPixmapItemArea::MyRasterPixmapItemArea()
{

}

int MyRasterPixmapItemArea::type() const
{
    return 65536; // represents a custom item
}


