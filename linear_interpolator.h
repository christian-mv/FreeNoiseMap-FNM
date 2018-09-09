#ifndef LINEAR_INTERPOLATOR_H
#define LINEAR_INTERPOLATOR_H

#include <utility>
#include <vector>
// https://bulldozer00.com/2016/05/10/linear-interpolation-in-c/

class Linear_Interpolator {
public:
    //On construction, we take in a vector of data point pairs
    //that represent the line we will use to interpolate
    Linear_Interpolator(const std::vector<std::pair<double, double>>&  points);
    ~Linear_Interpolator();

    //Computes the corresponding Y value
    //for X using linear interpolation
    double findValue(double x) const;

private:
    //Our container of (x,y) data points
    //std::pair::<double, double>.first = x value
    //std::pair::<double, double>.second = y value
    std::vector<std::pair<double, double>> _points;
};




#endif // LINEAR_INTERPOLATOR_H
