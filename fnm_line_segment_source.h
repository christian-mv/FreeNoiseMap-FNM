#ifndef FNM_LINE_SEGMENTSOURCE_H
#define FNM_LINE_SEGMENTSOURCE_H
#include "fnm_3D_segment.h"


class FnmLineSegmentSource : public Fnm3DSegment
{
public:
    explicit FnmLineSegmentSource() : Fnm3DSegment(), Lw_total(0){}

    void set_Lw_total(const double &Lw_total){this->Lw_total = Lw_total;}

    double get_Lw_total() const {return Lw_total;}   

private:   
    double Lw_total; // total sound power level in dB(A) units
};

#endif
