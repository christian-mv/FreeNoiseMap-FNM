#ifndef FNM_CORE_POINT_H
#define FNM_CORE_POINT_H

namespace fnm_core {

class Point
{
public:

    explicit Point(double in_x=0.0, double in_y=0.0,
                                double in_z=0.0);

    void set_x(const double &x);
    void set_y(const double &y);
    void set_z(const double &z);

    double get_x() const;
    double get_y() const;
    double get_z() const;
private:
    // current data
    double x, y, z; // current coordinates in meters units

};

}
#endif
