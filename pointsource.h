#ifndef POINTSOURCE_H
#define POINTSOURCE_H



class PointSource
{
public:

    explicit PointSource(double in_x=0.0, double in_y=0.0, double in_z=0.0, double in_Lw=-88.0);
    void set_x(const double &x){this->x = x;}
    void set_y(const double &y){this->y = y;}
    void set_z(const double &z){this->z = z;}
    void set_Lw(const double &z){this->z = z;}

    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_z() const {return z;}
    double get_Lw() const {return Lw;}
private:
    double x, y, z; // in meters units
    double Lw; // sound power in dB(A) units
};

#endif // POINTSOURCE_H
