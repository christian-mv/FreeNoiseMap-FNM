#ifndef SINGLE_RECEIVER_H
#define SINGLE_RECEIVER_H


class SingleReceiver
{
public:

    explicit SingleReceiver(double in_x=0.0, double in_y=0.0, double in_z=0.0, double in_Leq=-88.0);
    void set_x(const double &x){this->x = x;}
    void set_y(const double &y){this->y = y;}
    void set_z(const double &z){this->z = z;}
    void set_Leq(const double &Leq){this->Leq = Leq;}

    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_z() const {return z;}
    double get_Leq() const {return Leq;}
private:
    double x, y, z; // in meters units
    double Leq; // in dB(A) units
};

#endif // SINGLE_RECEIVER_H
