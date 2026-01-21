#ifndef FNM_CORE_POINT_SOURCE_H
#define FNM_CORE_POINT_SOURCE_H
#include "point.h"

namespace fnm_core {

class CorePointSource: public CorePoint
{
public:

    explicit CorePointSource(double in_x=0.0, double in_y=0.0,
                                double in_z=0.0, double in_Lw=-88.0):
        CorePoint(in_x, in_y, in_z), Lw(in_Lw){}

    void set_Lw(const double &Lw){this->Lw = Lw;}


    double get_Lw() const {return Lw;}
private:
    // current data
    double Lw; // total sound power level in dB(A) units

};

}
#endif // POINTSOURCE_H
