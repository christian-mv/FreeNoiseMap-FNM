#ifndef FNM_CORE_GRADIENT_COLOR_H
#define FNM_CORE_GRADIENT_COLOR_H

#include <tuple>
#include <vector>
#include <QVector>

#define COLOR_RGB std::tuple<double, double, double>



// THERE IS AN ERROR IN ANDROID WHEN USING std::vector instead of QVector
// this has to be fixed in the future in order to avoid Qt dependencies
// in the core functionality of FNM

namespace fnm {

class CoreGradientColor
{
public:
    CoreGradientColor();


    void addStep(double red, double green, double blue, double value);
    void sortStepsAscending();
    COLOR_RGB colorAt(const double &Leq);
    QVector<std::tuple<double, double, double, double>> getSteps() const;


private:
    // we store "value" three times for simplicity
    QVector <std::tuple<double, double, double, double>> steps;
    COLOR_RGB interpolateColor(const double &r1,
                               const double &g1,
                               const double &b1,
                               const double &r2,
                               const double &g2,
                               const double &b2,
                               const double & ratio);

};

}
#endif // GRADIENTCOLOR_H