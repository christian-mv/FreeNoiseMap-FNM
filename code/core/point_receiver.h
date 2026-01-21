#ifndef FNM_CORE_RECEIVER_H
#define FNM_CORE_RECEIVER_H
#include "point.h"

namespace fnm_core {

class PointReceiver: public Point
{

public:
    explicit PointReceiver(double in_x=0.0, double in_y=0.0,
                                   double in_z=0.0, double in_Leq=-88.0,
                                   bool interpolated = false):
        Point(in_x, in_y, in_z),
        Leq(in_Leq), interpolated(interpolated){}

    void set_Leq(const double &Leq){this->Leq = Leq;}

    double get_Leq() const {return Leq;}
    bool isInterpolated(){return interpolated;}

private:
    double Leq; // in dB(A) units
    bool interpolated; // true if the receiver is an interpolated receiver
};

}
#endif // SINGLE_RECEIVER_H
