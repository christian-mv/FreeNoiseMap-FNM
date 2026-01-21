#ifndef FNM_CORE_POINT_H
#define FNM_CORE_POINT_H

namespace fnm_core {

class CorePoint
{
public:

    explicit CorePoint(double in_x=0.0, double in_y=0.0,
                                double in_z=0.0):
        x(in_x), y(in_y), z(in_z){}

    void set_x(const double &x){this->x = x;}
    void set_y(const double &y){this->y = y;}
    void set_z(const double &z){this->z = z;}

    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_z() const {return z;}
private:
    // current data
    double x, y, z; // current coordinates in meters units

};

}
#endif
