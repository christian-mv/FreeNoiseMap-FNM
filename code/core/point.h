#ifndef FNM_CORE_POINT_H
#define FNM_CORE_POINT_H

#include <Eigen/Core>

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
    
    const Eigen::Vector3d& getVector() const { return vec; }
    void setVector(const Eigen::Vector3d& v) { vec = v; }

private:
    // current data
    Eigen::Vector3d vec;

};

}
#endif
