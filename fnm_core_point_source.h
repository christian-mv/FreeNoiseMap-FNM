#ifndef FNM_CORE_POINT_SOURCE_H
#define FNM_CORE_POINT_SOURCE_H


class FnmCorePointSource
{
public:

    explicit FnmCorePointSource(double in_x=0.0, double in_y=0.0,
                                double in_z=0.0, double in_Lw=-88.0):
        x(in_x), y(in_y), z(in_z), Lw(in_Lw){}

    void set_x(const double &x){this->x = x;}
    void set_y(const double &y){this->y = y;}
    void set_z(const double &z){this->z = z;}
    void set_Lw(const double &Lw){this->Lw = Lw;}

    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_z() const {return z;}
    double get_Lw() const {return Lw;}
private:
    // current data
    double x, y, z; // current coordinates in meters units
    double Lw; // total sound power level in dB(A) units

};

#endif // POINTSOURCE_H
