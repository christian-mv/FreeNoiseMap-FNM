#ifndef MINIMAL_ACOUSTIC_BARRIER_H
#define MINIMAL_ACOUSTIC_BARRIER_H


/*
 * This barrier is essentially defined as a line
 * and a height
*/

class MinimalAcousticBarrier
{
public:
    explicit MinimalAcousticBarrier();
    ~MinimalAcousticBarrier();

    void set_x1(const double &x1){this->x1 = x1;}
    void set_y1(const double &y1){this->y1 = y1;}

    void set_x2(const double &x2){this->x2 = x2;}
    void set_y2(const double &y2){this->y2 = y2;}

    void set_p1(const double &x, const double &y);
    void set_p2(const double &x, const double &y);

    double get_x1() const {return x1;}
    double get_y1() const {return y1;}


    double get_x2() const {return x2;}
    double get_y2() const {return y2;}

    double get_height() const {return height;}


    double distance() const;
    void moveBy(const double &dx, const double &dy);

private:
    // current data
    double x1, y1; // vertice 1
    double x2, y2; // vertice 2
    double height; // in meters
};

#endif // MINIMAL_ACOUSTIC_BARRIER_H

