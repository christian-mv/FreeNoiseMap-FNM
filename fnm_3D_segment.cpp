#include "fnm_3D_segment.h"
#include "noise_engine.h"
Fnm3DSegment::Fnm3DSegment() :
    x1(0), y1(0), z1(0)
{

}

void Fnm3DSegment::set_p1(const double &x, const double &y, const double &z)
{
    x1 = x;
    y1 = y;
    z1 = z;
}

void Fnm3DSegment::set_p2(const double &x, const double &y, const double &z)
{
    x2 = x;
    y2 = y;
    z2 = z;
}

double Fnm3DSegment::distance() const
{
    return NoiseEngine::distanceBetweenPoints(x1, y1, z1, x2, y2, z2);
}

void Fnm3DSegment::moveBy(const double &dx, const double &dy, const double &dz)
{
    x1+=dx;
    y1+=dy;
    z1+=dz;

    x2+=dx;
    y2+=dy;
    z2+=dz;
}
