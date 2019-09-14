#ifndef FNM_CORE_SINGLE_RECEIVER_H
#define FNM_CORE_SINGLE_RECEIVER_H
#include <QDebug>

class FnmCoreSingleReceiver
{
public:

    explicit FnmCoreSingleReceiver(double in_x=0.0, double in_y=0.0,
                            double in_z=0.0, double in_Leq=-88.0,
                             bool interpolated = false):
        x(in_x), y(in_y), z(in_z), Leq(in_Leq), interpolated(interpolated){}

    void set_x(const double &x){this->x = x;}
    void set_y(const double &y){this->y = y;}
    void set_z(const double &z){this->z = z;}
    void set_Leq(const double &Leq){this->Leq = Leq;}

    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_z() const {return z;}
    double get_Leq() const {return Leq;}
    bool isInterpolated(){return interpolated;}

private:
    double x, y, z; // in meters units
    double Leq; // in dB(A) units
    bool interpolated; // true if the receiver is an interpolated receiver
};

#endif // SINGLE_RECEIVER_H
