#include "point_source.h"

namespace fnm_core {

PointSource::PointSource(double in_x, double in_y, double in_z, double in_Lw) :
    Point(in_x, in_y, in_z), Lw(in_Lw)
{
}

void PointSource::set_Lw(const double &Lw)
{
    this->Lw = Lw;
}

double PointSource::get_Lw() const
{
    return Lw;
}

}
