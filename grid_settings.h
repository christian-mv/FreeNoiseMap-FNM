#ifndef GRID_SETTINGS_H
#define GRID_SETTINGS_H


class GridSettings
{
public:
    explicit GridSettings(double x=0.0, double y=0.0, double z=0.0,
                       double width=0.0, double height=0.0,
                       double dx=0.0, double dy=0.0);

    void setX(double x){ this->x=x; }
    void setY(double y){ this->y=y; }
    void setZ(double z){ this->z=z; }
    void setWidth(double width){ this->width=width; }
    void setHeight(double height){ this->height=height; }
    void setDeltaX(double dx){ this->dx=dx; }
    void setDeltaY(double dy){ this->dy=dy; }

    double getX(){ return x; }
    double getY(){ return y; }
    double getZ(){ return z; }
    double getWidth(){ return width; }
    double getHeight(){ return height; }
    double getDeltaX(){ return dx; }
    double setDeltaY(){ return dy; }

private:
    double x, y, z;
    double width, height;
    double dx, dy;
};

#endif // NOISEGRID_H
