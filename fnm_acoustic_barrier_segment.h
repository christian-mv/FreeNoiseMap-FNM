#ifndef FNM_ACOUSTIC_BARRIER_SEGMENT_H
#define FNM_ACOUSTIC_BARRIER_SEGMENT_H
#include "fnm_3D_segment.h"

/*
 * This barrier is essentially defined as a line
 * and a height
*/

class FnmAcousticBarrierSegment : public Fnm3DSegment
{
public:
    explicit FnmAcousticBarrierSegment(): Fnm3DSegment(), height(10){}
    ~FnmAcousticBarrierSegment();
    double get_height() const {return height;}
    void set_height(double value){this->height = value;}

private:
    double height; // in meters
};

#endif // MINIMAL_ACOUSTIC_BARRIER_H

