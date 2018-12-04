#ifndef LINESOURCE_H
#define LINESOURCE_H



/*LineSource hereda los atributos de PointSource donde (x,y,z) es la
Posición del primer vertice y Lw el nivel de potencia acústica total*/

class LineSource
{
public:
    explicit LineSource(double in_x1=0.0, double in_y1=0.0, double in_z1=0.0,
                        double in_x2=0.0, double in_y2=0.0, double in_z2=0.0,
                        double in_Lw_total=-88.0);

    void set_x1(const double &x1){this->x1 = x1;}
    void set_y1(const double &y1){this->y1 = y1;}
    void set_z1(const double &z1){this->z1 = z1;}

    void set_x2(const double &x2){this->x2 = x2;}
    void set_y2(const double &y2){this->y2 = y2;}
    void set_z2(const double &z2){this->z2 = z2;}

    void set_Lw_total(const double &Lw_total){this->Lw_total = Lw_total;}

    double get_x1() const {return x1;}
    double get_y1() const {return y1;}
    double get_z1() const {return z1;}

    double get_x2() const {return x2;}
    double get_y2() const {return y2;}
    double get_z2() const {return z2;}

    double get_Lw_total() const {return Lw_total;}
private:
    // current data
    double x1, y1, z1; // vertice 1
    double x2, y2, z2; // vertice 2
    double Lw_total; // total sound power level in dB(A) units
};

#endif // LINESOURCE_H
