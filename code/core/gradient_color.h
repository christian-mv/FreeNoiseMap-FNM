#ifndef FNM_CORE_GRADIENT_COLOR_H
#define FNM_CORE_GRADIENT_COLOR_H

#include <tuple>
#include <vector>

namespace fnm_core {

using ColorRGB = std::tuple<double, double, double>;

class GradientColor
{
public:
    GradientColor();


    void addStep(double red, double green, double blue, double value);
    void sortStepsAscending();
    ColorRGB colorAt(const double &Leq);
    std::vector<std::tuple<double, double, double, double>> getSteps() const;


private:
    // we store "value" three times for simplicity
    std::vector <std::tuple<double, double, double, double>> steps;
    ColorRGB interpolateColor(const double &r1,
                               const double &g1,
                               const double &b1,
                               const double &r2,
                               const double &g2,
                               const double &b2,
                               const double & ratio);

};

}
#endif // GRADIENTCOLOR_H
