#include "gradient_color.h"
#include <QDebug>

namespace fnm {

CoreGradientColor::CoreGradientColor()
{

//    // try the next values
//    addStep(0/255,      255/255,    0/255,      35/255);
//    addStep(85/255,     170/255,    0/255,      40/255);
//    addStep(255/255,    255/255,    0/255,      45/255);
//    addStep(197/255,    131/255,    0/255,      50/255);
//    addStep(255/255,    92/255,     11/255,     55/255);
//    addStep(255/255,    0/255,      0/255,      60/255);
//    addStep(156/255,    0/255,      0/255,      65/255);
//    addStep(85/255,     0/255,      127/255,    70/255);
//    addStep(0/255,      0/255,      150/255,    75/255);
//    addStep(0/255,      0/255,      113/255,    80/255);


}

void CoreGradientColor::addStep(double red, double green, double blue, double value)
{

    if(red<0 || red >1 || green<0 || green >1 || blue<0 || blue >1){
        throw std::out_of_range("GradientColor::addStep only accept values"
                                "between 0 and 1");
    }

    std::tuple<double, double, double, double> temp {red, green, blue, value};
     steps.push_back(temp);
}

void CoreGradientColor::sortStepsAscending()
{
//     https://stackoverflow.com/questions/23030267/custom-sorting-a-vector-of-tuples
    std::sort(steps.begin(),steps.end(),
         [](const std::tuple<double,double,double,double>& a,
         const std::tuple<double,double,double,double>& b) -> bool
    {
        return std::get<3>(a) < std::get<3>(b);
    });
}


COLOR_RGB CoreGradientColor::colorAt(const double &Leq)
{
    COLOR_RGB colorResult;


    double ratio; // between 0 and 1
    double Leq1, Leq2;


    if(steps.size()<=1){
        // WRITE HERE

    }
    else{
        sortStepsAscending();
        for(int i = 0; i<steps.size()-1; ++i){
            if(std::get<3>(steps.at(i)) <=Leq && Leq<=std::get<3>(steps.at(i+1))){
//                color_1 = {
//                    std::get<0>(steps.at(i)),
//                    std::get<1>(steps.at(i)),
//                    std::get<2>(steps.at(i))
//                };

//                color_2 = {
//                    std::get<0>(steps.at(i+1)),
//                    std::get<1>(steps.at(i+1)),
//                    std::get<2>(steps.at(i+1))
//                };

                Leq1 =  std::get<3>(steps.at(i));
                Leq2 =  std::get<3>(steps.at(i+1));

                ratio = (Leq-Leq1)/(Leq2-Leq1);
                colorResult =interpolateColor( std::get<0>(steps.at(i)),
                                         std::get<1>(steps.at(i)),
                                         std::get<2>(steps.at(i)),
                                         std::get<0>(steps.at(i+1)),
                                         std::get<1>(steps.at(i+1)),
                                         std::get<2>(steps.at(i+1)),
                                         ratio);
                break;
            }
        }
    }

    return colorResult;
}

QVector<std::tuple<double, double, double, double>> CoreGradientColor::getSteps() const
{
    return this->steps;
}



COLOR_RGB CoreGradientColor::interpolateColor(const double &r1, /* https://www.alanzucconi.com/2016/01/06/colour-interpolation/*/
                                          const double &g1,
                                          const double &b1,
                                          const double &r2,
                                          const double &g2,
                                          const double &b2,
                                          const double & ratio)
{
    COLOR_RGB color {
        r1 + (r2 - r1) * ratio,
        g1 + (g2 - g1) * ratio,
        b1 + (b2 - b1) * ratio
    };
    return color;
}

}