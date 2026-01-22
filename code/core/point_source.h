#ifndef FNM_CORE_POINT_SOURCE_H
#define FNM_CORE_POINT_SOURCE_H
#include "point.h"

namespace fnm_core {

class PointSource: public Point
{
public:

    explicit PointSource(double in_x=0.0, double in_y=0.0,
                                double in_z=0.0, double in_Lw=-88.0);

    void set_Lw(const double &Lw);


    double get_Lw() const;
private:
    // current data
    double Lw; // total sound power level in dB(A) units

};

}
#endif // POINTSOURCE_H
