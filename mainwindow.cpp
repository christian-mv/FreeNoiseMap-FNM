#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noise_engine.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    loadCursors();

    loadDefaultGrid();

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setMouseTracking(true); // enabling mouse track on a scene when not pressing mouse
    qApp->installEventFilter(this);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop );
    ui->graphicsView->centerOn(QPointF(0,0));
    ui->graphicsView->scale(1.5,-1.5); // invert Y axes




    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// this method is necessary to compasate the reflection of Y axes
QImage MainWindow::invertImageOnYAxes(const QImage &image)
{
    QPoint center = image.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.scale(1,-1);
    return image.transformed(matrix);
}

void MainWindow::loadCursors()
{

    myCursors["pointSource"] = QCursor(
                QPixmap(":/images/icons/point_source.png").scaled(20,20,Qt::KeepAspectRatio) );

    myCursors["grid"] = QCursor(
                QPixmap(":/images/icons/grid.png").scaled(20,20,Qt::KeepAspectRatio) );

       myCursors["arrowCursor"] = QCursor(Qt::ArrowCursor);

       myCursors["grid_edit"] = QCursor(Qt::CrossCursor);

}

void MainWindow::loadDefaultGrid()
{
    myGrid.setRect(QRectF(0, 0, 300, 300));
    myGrid.setDeltaX(1);
    myGrid.setDeltaY(1);
    myGrid.setInterpolationFactor(1);
    receivers.setGrid(myGrid);

    // create and image which its resolution depends on the screen resolution (tested with 1360X768 screen)
    qreal side = qMin(myGrid.getRect().width(), myGrid.getRect().height());
    qreal side2 = qMax(qApp->desktop()->width(), qApp->desktop()->height());


    image = new QImage(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);
    image->fill(Qt::white);



    image->save("../test.png", "PNG");


    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));

    pixmapItem.setScale(side/side2); // to represent the real size in the scene

    scene.setBackgroundBrush(Qt::darkGray);
    scene.addItem(&pixmapItem);
    pixmapItem.setPos(myGrid.get_x(), myGrid.get_y());


}

bool MainWindow::calculateNoiseFromSources()
{
    if(pointSources.size() == 0){
        return false;
    }

    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
//    progress.setWindowTitle(QObject::tr("NAME APP"));
    progress.setLabelText(QObject::tr("Calculating..."));
    progress.setMinimum(0);
    progress.setMaximum(receivers.matrix.size()- 1);
    progress.show();


    for(int i = 0; i<receivers.matrix.size(); i++){
        for(auto currentReceiver : receivers.matrix.at(i)){
            for(auto currentSource : pointSources){
                NoiseEngine::P2P(currentSource, currentReceiver);
            }

        }
        progress.setValue(i);
        qApp->processEvents();
    }
    progress.setValue( progress.maximum() );
    return true;
}






bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(target == &scene){
        if (event->type() == QEvent::GraphicsSceneMouseMove)
          {
            QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent*>(event);


            QString str = QString("x: %1 m, y: %2 m")
                                    .arg(sceneEvent->scenePos().x())
                                    .arg(sceneEvent->scenePos().y());

            statusBar()->showMessage(str);
          }

        else if (event->type() == QEvent::GraphicsSceneMousePress && cursor()==this->myCursors["pointSource"])
          {
            QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

            pointSources.push_back(new PointSource(
                                       sceneEvent->scenePos().x(),
                                       sceneEvent->scenePos().y(),
                                       1.2,90));
          }
    }
    return false;
}



void MainWindow::on_actionAdd_point_source_triggered()
{
    setCursor(myCursors["pointSource"]);

}


void MainWindow::on_actioneditMode_triggered()
{
    setCursor(myCursors["arroCursor"]);
}

void MainWindow::on_actiongrid_triggered()
{
    setCursor(myCursors["grid_edit"]);
}

void MainWindow::on_actioncalculateGrid_triggered()
{

    receivers.resetNoiseReceiver();
    calculateNoiseFromSources();
    receivers.paintGrid(*image, myGrid);
    image->save("../test.png", "PNG");


    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));
}
