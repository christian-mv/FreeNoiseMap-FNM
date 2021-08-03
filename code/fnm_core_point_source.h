#ifndef FNM_CORE_POINT_SOURCE_H
#define FNM_CORE_POINT_SOURCE_H
#include "fnm_core_point.h"

class FnmCorePointSource: public FnmCorePoint
{
public:

    explicit FnmCorePointSource(double in_x=0.0, double in_y=0.0,
                                double in_z=0.0, double in_Lw=-88.0):
        FnmCorePoint(in_x, in_y, in_z), Lw(in_Lw){}

    void set_Lw(const double &Lw){this->Lw = Lw;}


    double get_Lw() const {return Lw;}
private:
    // current data
    double Lw; // total sound power level in dB(A) units

};

#endif // POINTSOURCE_H
