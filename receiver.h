#ifndef RECEIVER_H
#define RECEIVER_H


class Receiver
{
public:
    explicit Receiver(double x=0.0, double y=0.0, double z=0.0, double Leq=-88.0);

    void set_x(const double &x){this->x = x;}
    void set_y(const double &y){this->y = y;}
    void set_z(const double &z){this->z = z;}
    void set_Leq(const double &z){this->z = z;}

    double get_x(){return x;}
    double get_y(){return y;}
    double get_z(){return z;}


private:
    double x, y, z; // in meters units
    double Leq; // in dB(A) units


};

#endif // RECEIVER_H
