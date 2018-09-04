#ifndef GRID_SETTINGS_H
#define GRID_SETTINGS_H
#include<QRectF>

class GridSettings
{
public:
    GridSettings();
    explicit GridSettings(QRectF rect);

    void setRect(const QRectF &newRect){ this->rectGrid = newRect; }
    void setDeltaX(const double &dx=10){ this->dx=dx; }
    void setDeltaY(const double &dy=10){ this->dy=dy; }

    QRectF getRect() const { return this->rectGrid; }
    double getDeltaX() const { return dx; }
    double getDeltaY() const { return dy; }
    unsigned int countRows();
    unsigned int countColumns();

private:
    QRectF rectGrid;
    double dx=10, dy=10;

};

#endif // NOISEGRID_H
