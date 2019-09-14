#ifndef FNM_CORE_3D_SEGMENT_H
#define FNM_CORE_3D_SEGMENT_H


class FnmCore3DSegment
{
public:
    FnmCore3DSegment();

    void set_x1(const double &x1){this->x1 = x1;}
    void set_y1(const double &y1){this->y1 = y1;}
    void set_z1(const double &z1){this->z1 = z1;}

    void set_x2(const double &x2){this->x2 = x2;}
    void set_y2(const double &y2){this->y2 = y2;}
    void set_z2(const double &z2){this->z2 = z2;}

    void set_p1(const double &x, const double &y, const double &z);
    void set_p2(const double &x, const double &y, const double &z);

    double get_x1() const {return x1;}
    double get_y1() const {return y1;}
    double get_z1() const {return z1;}

    double get_x2() const {return x2;}
    double get_y2() const {return y2;}
    double get_z2() const {return z2;}

    double distance() const;
    void moveBy(const double &dx, const double &dy, const double &dz);

private:
    // current data
    double x1, y1, z1; // vertice 1
    double x2, y2, z2; // vertice 2

};

#endif // FNM3DSEGMENT_H
