#include "point.h"

namespace fnm_core {

Point::Point(double in_x, double in_y, double in_z) :
    vec(in_x, in_y, in_z)
{
}

void Point::set_x(const double &x)
{
    vec.x() = x;
}

void Point::set_y(const double &y)
{
    vec.y() = y;
}

void Point::set_z(const double &z)
{
    vec.z() = z;
}

double Point::get_x() const
{
    return vec.x();
}

double Point::get_y() const
{
    return vec.y();
}

double Point::get_z() const
{
    return vec.z();
}

}
