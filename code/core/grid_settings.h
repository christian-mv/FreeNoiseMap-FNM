#ifndef FNM_CORE_GRID_SETTINGS_H
#define FNM_CORE_GRID_SETTINGS_H
#include<QRectF>

namespace fnm_core {

class GridSettings
{
public:
    GridSettings();
    explicit GridSettings(QRectF rect);

    void setRect(const QRectF &newRect){ this->rectGrid = newRect; }
    void setDeltaX(const double &dx=10){ this->dx=dx; }
    void setDeltaY(const double &dy=10){ this->dy=dy; }
    void setInterpolationFactor(const unsigned int &factor=1){factor<1? 1 : interpolationFactor = factor; }

    QRectF getRect() const { return this->rectGrid; }
    double getDeltaX() const { return dx; }
    double getDeltaY() const { return dy; }
    double getLeft() const {return rectGrid.left();}
    double getRight() const {return rectGrid.right();}
    double get_x() const {return rectGrid.x();}
    double get_y() const {return rectGrid.y();}
    double getTop() const {return rectGrid.top();}
    double getBottom() const {return rectGrid.bottom();}
    unsigned int getInterpolatorFactor() const { return interpolationFactor;}

    unsigned int countRows();
    unsigned int countColumns();

private:
    QRectF rectGrid; //represent the extension of the coordinate system
    double dx, dy;
    unsigned int interpolationFactor;

};

}
#endif // NOISEGRID_H
