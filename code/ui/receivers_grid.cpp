#include "receivers_grid.h"
#include <QtDebug>
#include <tuple>
#include <QtWidgets>
using namespace std;

namespace fnm_ui {

ReceiversGrid::ReceiversGrid()
{
    // Defining default gradien.
    gradientColor.addStep(0.0/255.0,      255.0/255.0,      0.0/255.0,      -88.0);
    gradientColor.addStep(0.0/255.0,      255.0/255.0,      0.0/255.0,      35.0);
    gradientColor.addStep(85.0/255.0,     170.0/255.0,      0.0/255.0,      40.0);
    gradientColor.addStep(255.0/255.0,    255.0/255.0,      0.0/255.0,      45.0);
    gradientColor.addStep(197.0/255.0,    131.0/255.0,      0.0/255.0,      50.0);
    gradientColor.addStep(255.0/255.0,    92.0/255.0,       11.0/255.0,     55.0);
    gradientColor.addStep(255.0/255.0,    0.0/255.0,         0.0/255.0,     60.0);
    gradientColor.addStep(156.0/255.0,    0.0/255.0,        0.0/255.0,      65.0);
    gradientColor.addStep(85.0/255.0,     0/255.0,          127.0/255.0,    70.0);
    gradientColor.addStep(0.0/255.0,      0/255.0,          150.0/255.0,    75.0);
    gradientColor.addStep(0.0/255.0,      0.0/255.0,        113.0/255.0,    80.0);
    gradientColor.addStep(0.0/255.0,      0.0/255.0,        113.0/255.0,    120.0);


    gradientColor.sortStepsAscending();

}

void ReceiversGrid::setNoiseGrid(fnm_core::NoiseGrid* grid)
{
    this->noiseGrid = grid;
}

void ReceiversGrid::setGradient(const fnm_core::GradientColor gradientColor)
{
    this->gradientColor = gradientColor;
    this->gradientColor.sortStepsAscending();
}


bool ReceiversGrid::paintGrid(QImage &image, QProgressDialog &progress)
{
    if(!noiseGrid) return false;

    const auto& matrix = noiseGrid->getMatrix();
    const auto& gridSettings = noiseGrid->getSettings();

    // it is necessary redefine the maximum steps of the progress dialog since interpolation
    // could change the size of matriz
    progress.setMaximum(static_cast<int>(matrix.size())+1);

    QPainter painter(&image);

    // painter.translate(myGrid.getRect().bottomLeft());
    painter.translate(gridSettings.getRect().left(), gridSettings.getRect().bottom());

    painter.translate(-gridSettings.getRect().left() /*+ myGrid.getDeltaX()/2*/,
                      gridSettings.getRect().top() /*- myGrid.getDeltaY()/2*/);

    painter.scale(1, -1);



//    // set logical coordinates according to gridSettings area
    // painter.setWindow(gridSettings.getRect().toRect());
    QRect rect(gridSettings.getRect().x,
               gridSettings.getRect().y,
               gridSettings.getRect().width,
               gridSettings.getRect().height);
    painter.setWindow(rect);


    // set paint properties
//    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::NoPen);
    painter.setPen(pen);


    // calculate single rectangles
    QColor decibelColor;

    for(unsigned int i = 0; i<matrix.size(); i++){

        if(progress.wasCanceled()){
            progress.close();
            return false;
        }

        for(unsigned int j = 0; j<matrix.at(i).size(); j++){

            const auto &r = matrix.at(i).at(j);

            setNoiseColor(r.get_Leq(), &decibelColor);
            painter.setBrush(QBrush(decibelColor));
            painter.drawRect(receiverRect(r));
        }

        qApp->processEvents();
        progress.setValue( static_cast<int>(i) );
    }
    progress.close();
    return true;
}

void ReceiversGrid::setNoiseColor(const double Leq, QColor * colorDecibel)
{
    tuple<double, double, double> colorTuple;

    colorTuple = gradientColor.colorAt(Leq);
    colorDecibel->setRgb(static_cast<int>( 255*std::get<0>(colorTuple) ),
                          static_cast<int>( 255*std::get<1>(colorTuple) ),
                          static_cast<int>( 255*std::get<2>(colorTuple) ),
                          255);
}


QRectF  ReceiversGrid::receiverRect(const fnm_core::PointReceiver &receiver)
{

    return receiverRect(receiver.get_x(), receiver.get_y());
}


QRectF ReceiversGrid::receiverRect(const double x, const double y)
{
    if(!noiseGrid) return QRectF();
    const auto& gridSettings = noiseGrid->getSettings();

    unsigned int n = gridSettings.getInterpolatorFactor();
    double dx = gridSettings.getDeltaX();
    double dy = gridSettings.getDeltaY();
    double width = dx/n;
    double height = dy/n;

    return QRectF(x - width/2,
                      y - height/2,
                      width,
                      height
                  );
}

}