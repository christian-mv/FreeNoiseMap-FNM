#include "point_receiver.h"

namespace fnm_core {

PointReceiver::PointReceiver(double in_x, double in_y, double in_z, double in_Leq, bool interpolated) :
    Point(in_x, in_y, in_z),
    Leq(in_Leq), interpolated(interpolated)
{
}

void PointReceiver::set_Leq(const double &Leq)
{
    this->Leq = Leq;
}

double PointReceiver::get_Leq() const
{
    return Leq;
}

bool PointReceiver::isInterpolated() const
{
    return interpolated;
}

}
