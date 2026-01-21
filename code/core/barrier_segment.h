#ifndef FNM_CORE_BARRIER_SEGMENT_H
#define FNM_CORE_BARRIER_SEGMENT_H
#include "3D_segment.h"

/*
 * This acoustic barrier is essentially defined as a line
 * with a height
*/
namespace fnm_core {

class BarrierSegment : public Segment
{
public:
    explicit BarrierSegment(): Segment(), height(10){}
    double get_height() const {return height;}
    void set_height(double value){this->height = value;}

private:
    double height; // in meters
};

}
#endif // MINIMAL_ACOUSTIC_BARRIER_H
