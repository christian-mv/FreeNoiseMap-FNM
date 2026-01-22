#include "point.h"

namespace fnm_core {

Point::Point(double in_x, double in_y, double in_z) :
    x(in_x), y(in_y), z(in_z)
{
}

void Point::set_x(const double &x)
{
    this->x = x;
}

void Point::set_y(const double &y)
{
    this->y = y;
}

void Point::set_z(const double &z)
{
    this->z = z;
}

double Point::get_x() const
{
    return x;
}

double Point::get_y() const
{
    return y;
}

double Point::get_z() const
{
    return z;
}

}
