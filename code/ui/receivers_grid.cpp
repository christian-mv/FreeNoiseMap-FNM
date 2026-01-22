#include "receivers_grid.h"
#include "noise_engine.h"
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

ReceiversGrid::ReceiversGrid(const fnm_core::GridSettings &settings)
{    
    setGrid(settings);

}

void ReceiversGrid::setGrid(const fnm_core::GridSettings &gridSettings)
{
    this->gridSettings = gridSettings;
    unsigned int nRows = this->gridSettings.countRows();
    unsigned int nColumns = this->gridSettings.countColumns();


    setMatrixOfReceivers(nRows, nColumns); // set this->matrix memeber
//    qDebug()<<matrix.size();
    for(unsigned int i = 0; i < nRows; i++){
        for(unsigned int j = 0; j < nColumns; j++){
//            qDebug()<<i<<" , "<<j;
            matrix.at(j).at(i) = fnm_core::PointReceiver(gridSettings.getLeft()
                                                    + i*gridSettings.getDeltaX(),
                                                    gridSettings.getTop()+j*gridSettings.getDeltaY(),
                                                    0, -88.0,
                                                    false); //matrix.[i][j];
//            qDebug()<<matrix.at(j).at(i)->get_x()<<" , " <<matrix.at(j).at(i)->get_y();
        }
    }


}

void ReceiversGrid::setGradient(const fnm_core::GradientColor gradientColor)
{
    this->gradientColor = gradientColor;
    this->gradientColor.sortStepsAscending();
}

void ReceiversGrid::setMatrixOfReceivers(unsigned int n, unsigned int m)
{
    matrix.resize(m);
    for(unsigned int i = 0 ; i < m ; ++i){
        matrix[i].resize(n);
    }
}

bool ReceiversGrid::paintGrid(QImage &image, const fnm_core::GridSettings &myGrid, QProgressDialog &progress)
{



    // it is necessary redefine the maximum steps of the progress dialog since interpolation
    // could change the size of matriz
    progress.setMaximum(static_cast<int>(matrix.size())+1);

    QPainter painter(&image);

    // painter.translate(myGrid.getRect().bottomLeft());
    painter.translate(myGrid.getRect().left(), myGrid.getRect().bottom());

    painter.translate(-myGrid.getRect().left() /*+ myGrid.getDeltaX()/2*/,
                      myGrid.getRect().top() /*- myGrid.getDeltaY()/2*/);

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


//    if(Leq <= 35){ // dB units
//        colorDecibel->setRgb(0, 255, 0, 255);
//    }
//    else if(35<Leq && Leq<=40){
//        colorDecibel->setRgb(85, 170, 0, 255);
//    }
//    else if(40<Leq && Leq<=45){
//        colorDecibel->setRgb(255, 255, 0, 255);
//    }
//    else if(45<Leq && Leq<=50){
//        colorDecibel->setRgb(197, 131, 0, 255);
//    }
//    else if(50<Leq && Leq<=55){
//        colorDecibel->setRgb(255, 92, 11, 255);
//    }
//    else if(55<Leq && Leq<=60){
//        colorDecibel->setRgb(255, 0, 0, 255);
//    }
//    else if(60<Leq && Leq<=65){
//        colorDecibel->setRgb(156, 0, 0, 255);
//    }
//    else if(65<Leq && Leq<=70){
//        colorDecibel->setRgb(85, 0, 127, 255);
//    }
//    else if(70<Leq && Leq<=75){
//        colorDecibel->setRgb(0, 0, 150, 255);
//    }
//    else if(75<Leq && Leq<=80){
//        colorDecibel->setRgb(0, 0, 113, 255);
//    }
//    else if(80<Leq){
//        colorDecibel->setRgb(0, 0, 0, 255);
//    }

}

void ReceiversGrid::resetNoiseReceiver()
{
    for(auto &row: matrix){
        for(auto &receiver: row){
            receiver.set_Leq(-88);
        }
    }
}



//string ReceiversGrid::gridStatistics()
//{
//    unsigned int countInterpolated = 0;
//    unsigned int countNoInterpolated = 0;
//    for(auto row: matrix){
//        for(auto receiver: row)
//            if(receiver->isInterpolated()){
//                countInterpolated++;
//            }
//            else
//            {
//                countNoInterpolated++;
//            }
//    }

//    string result;

//    // to_string() is not supported for android NDK
//    result = "interpolated receivers: " + countInterpolated
//            +" no interpolated receivers: " + countInterpolated ;

//    return result;
//}

void ReceiversGrid::interpolateGrid()
{
    unsigned int factor = getGridSettings().getInterpolatorFactor();
    if(factor<=1){return;}

    double dx = getGridSettings().getDeltaX()/factor;
    double dy = getGridSettings().getDeltaY()/factor;
    double Leqx_temp; // here store interpolated Leq on x axes.
    double Leqy_temp; // here store interpolated Leq on y axes.

    //  interpolated rectangles on x axes
    for(unsigned int i = 0; i<matrix.size(); i++){
        for(unsigned int j = 0; j<matrix.at(i).size(); j=j+factor){

            const auto &r = matrix.at(i).at(j);
            if(j<matrix.at(i).size()-1){
                for(unsigned int k=1; k<factor; k++){

                    fnm_core::NoiseEngine::interpolationValueAt(r.get_x(),
                                                      r.get_Leq(),
                                                      r.get_x()+k*dx,
                                                      Leqx_temp,
                                                      matrix.at(i).at(j+1).get_x(),
                                                      matrix.at(i).at(j+1).get_Leq());


                    matrix.at(i).insert(matrix.at(i).begin()+j+1,
                                                   fnm_core::PointReceiver(r.get_x()+k*dx,
                                                                      r.get_y(),
                                                                      r.get_z(),
                                                                      Leqx_temp,true));
                } // for k
            }// if
        } // for j
    } // for i




    // interpolated rectangles on y axes

    // centinel is a copy of the last row
    std::vector<fnm_core::PointReceiver> centinel = matrix.back();

    for(unsigned int i = 0; ; i=i+factor){

        // compare row content (simplified check)
        bool isLast = true;
        if(matrix.at(i).size() != centinel.size()) isLast = false;
        else {
            for(size_t idx=0; idx<matrix.at(i).size(); ++idx) {
                if(matrix.at(i).at(idx).get_x() != centinel.at(idx).get_x() ||
                   matrix.at(i).at(idx).get_y() != centinel.at(idx).get_y()) {
                    isLast = false;
                    break;
                }
            }
        }

        if(isLast) // break when the last row is reached
        {
            break;
        }

        vector<vector<fnm_core::PointReceiver>> tempMatrix; // esto es una matriz intermedia de receptores
        for(unsigned int k=1; k<factor; k++){
            vector<fnm_core::PointReceiver> temprow;
            for(unsigned int j = 0; j<matrix.at(i).size(); j++){

                const auto &r = matrix.at(i).at(j);

                fnm_core::NoiseEngine::interpolationValueAt(r.get_y(),
                                                  r.get_Leq(),
                                                  r.get_y()+k*dy,
                                                  Leqy_temp,
                                                  matrix.at(i+1).at(j).get_y(),
                                                  matrix.at(i+1).at(j).get_Leq());


                temprow.push_back(fnm_core::PointReceiver(r.get_x(),
                                                     r.get_y()+k*dy,
                                                     r.get_z(),
                                                     Leqy_temp,true));

            } // for: j

            tempMatrix.push_back(temprow);

        }// for: k
        matrix.insert(matrix.begin()+i+1,tempMatrix.begin(), tempMatrix.end());
        i += (factor - 1); // skip the newly inserted rows
    } // for: i
}

void ReceiversGrid::clearInterpolatedReceivers()
{
    // delete full interpolated rows
    for (auto it = matrix.begin(); it != matrix.end(); ) {
        if (!it->empty() && it->at(0).isInterpolated()) {
            it = matrix.erase(it);
        } else {
            ++it;
        }
    }

    // delete interpolated receivers located in between of no-interpolated receivers
    for(unsigned int i=0; i<matrix.size(); i++){
        for (auto it = matrix.at(i).begin(); it != matrix.at(i).end(); ) {
            if (it->isInterpolated()) {
                it = matrix.at(i).erase(it);
            } else {
                ++it;
            }
        }
    }

}


QRectF  ReceiversGrid::receiverRect(const fnm_core::PointReceiver &receiver)
{

    return receiverRect(receiver.get_x(), receiver.get_y());
}


QRectF ReceiversGrid::receiverRect(const double x, const double y)
{
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
