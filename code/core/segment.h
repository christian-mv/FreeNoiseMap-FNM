#ifndef FNM_CORE_3D_SEGMENT_H
#define FNM_CORE_3D_SEGMENT_H

#include <Eigen/Core>

namespace fnm_core {

class Segment
{
public:
    Segment();

    void set_x1(const double &x1);
    void set_y1(const double &y1);
    void set_z1(const double &z1);

    void set_x2(const double &x2);
    void set_y2(const double &y2);
    void set_z2(const double &z2);

    void set_p1(const double &x, const double &y, const double &z);
    void set_p2(const double &x, const double &y, const double &z);
    
    void set_p1(const Eigen::Vector3d& p);
    void set_p2(const Eigen::Vector3d& p);

    double get_x1() const;
    double get_y1() const;
    double get_z1() const;

    double get_x2() const;
    double get_y2() const;
    double get_z2() const;
    
    const Eigen::Vector3d& get_p1_vec() const { return p1; }
    const Eigen::Vector3d& get_p2_vec() const { return p2; }

    double distance() const;
    void moveBy(const double &dx, const double &dy, const double &dz);

private:
    // current data
    Eigen::Vector3d p1; // vertice 1
    Eigen::Vector3d p2; // vertice 2

};

}
#endif // FNM3DSEGMENT_H
