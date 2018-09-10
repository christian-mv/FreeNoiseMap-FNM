#ifndef GRADIENTCOLOR_H
#define GRADIENTCOLOR_H

#include <tuple>
#include <vector>
#define STEP tuple<double, double, double, double>
#define COLOR_RGB tuple<double, double, double>


using namespace std;


class GradientColor
{
public:
    GradientColor();


    void addStep(double red, double green, double blue, double value);
    void sortStepsAscending();
    COLOR_RGB colorAt(const double &Leq);
    vector<STEP> getSteps() const;


private:
    // we store "value" three times for simplicity
    vector<STEP> steps;
    COLOR_RGB interpolateColor(const double &r1,
                               const double &g1,
                               const double &b1,
                               const double &r2,
                               const double &g2,
                               const double &b2,
                               const double & ratio);

};

#endif // GRADIENTCOLOR_H
