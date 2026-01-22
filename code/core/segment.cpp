#include "segment.h"

namespace fnm_core {

Segment::Segment() :
    p1(0,0,0), p2(0,0,0)
{
}

void Segment::set_x1(const double &x1) { p1.x() = x1; }
void Segment::set_y1(const double &y1) { p1.y() = y1; }
void Segment::set_z1(const double &z1) { p1.z() = z1; }

void Segment::set_x2(const double &x2) { p2.x() = x2; }
void Segment::set_y2(const double &y2) { p2.y() = y2; }
void Segment::set_z2(const double &z2) { p2.z() = z2; }

void Segment::set_p1(const double &x, const double &y, const double &z)
{
    p1 = Eigen::Vector3d(x, y, z);
}

void Segment::set_p2(const double &x, const double &y, const double &z)
{
    p2 = Eigen::Vector3d(x, y, z);
}

void Segment::set_p1(const Eigen::Vector3d& p) { p1 = p; }
void Segment::set_p2(const Eigen::Vector3d& p) { p2 = p; }

double Segment::get_x1() const { return p1.x(); }
double Segment::get_y1() const { return p1.y(); }
double Segment::get_z1() const { return p1.z(); }

double Segment::get_x2() const { return p2.x(); }
double Segment::get_y2() const { return p2.y(); }
double Segment::get_z2() const { return p2.z(); }

double Segment::distance() const
{
    return (p1 - p2).norm();
}

void Segment::moveBy(const double &dx, const double &dy, const double &dz)
{
    Eigen::Vector3d v(dx, dy, dz);
    p1 += v;
    p2 += v;
}

}
