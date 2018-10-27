#include "mainwindow.h"
#include "pointsource.h"
#include "ui_mainwindow.h"
#include "noise_engine.h"
#include "pointsourcepixmapitem.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QProgressDialog>
#include <QMessageBox>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);
    setWindowIcon(QIcon(":/images/icons/app_icon.png"));
    setWindowTitle(QString(MY_APP_NAME)+" - v"+QString(VERSION_OF_APP));

    loadCursors();

    loadDefaultGrid();

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setMouseTracking(true); // enabling mouse track on a scene when not pressing mouse
    qApp->installEventFilter(this);

    ui->graphicsView->centerOn(QPointF(0,0));
    ui->graphicsView->scale(1,-1); // invert Y axes


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
                QPixmap(":/images/icons/point_source.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));


    myCursors["grid"] = QCursor(
                QPixmap(":/images/icons/grid.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    myCursors["arrowMode"] = QCursor(Qt::ArrowCursor);

    myCursors["editMode"] = QCursor(Qt::PointingHandCursor);

    myCursors["gridMode"] = QCursor(Qt::CrossCursor);

    myCursors["dragMode"] = QCursor(Qt::OpenHandCursor);

}

void MainWindow::loadDefaultGrid()
{
    myGrid.setRect(QRectF(0, 0, 1000, 600));
    myGrid.setDeltaX(5);
    myGrid.setDeltaY(5);
    myGrid.setInterpolationFactor(1);
    receivers.setGrid(myGrid);

    resetPixmapArea();

    scene.setBackgroundBrush(Qt::darkGray);
    scene.addItem(&pixmapItem);
    pixmapItem.setPos(myGrid.get_x(), myGrid.get_y());


}

void MainWindow::resetPixmapArea(){

    qreal side = qMin(myGrid.getRect().width(), myGrid.getRect().height());
    qreal side2 = qMax(qApp->desktop()->width(), qApp->desktop()->height());

    image = new QImage(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);
    image->fill(Qt::white);


    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));

    pixmapItem.setScale(side/side2); // to represent the real size in the scene

}

void MainWindow::movingItemsOnTheScene(QPointF Pos)
{
    if (ui->graphicsView->cursor()==myCursors["arrowMode"] && scene.getShadedItemFlag()){


        QGraphicsItem *moving_item= scene.mouseGrabberItem();

        // the next conditional detects if no items or the rasterAreaItem were clicked


        if(moving_item!=nullptr && moving_item != &pixmapItem)
        {
            shaded_line->setLine(p1_shaded_line.x(),
                                 p1_shaded_line.y(),
                                 Pos.x(),
                                 Pos.y());

            moving_item->setPos(Pos); // this correct the position of the item to be more acurate
        }
    }
}

bool MainWindow::calculateNoiseFromSources(QProgressDialog &progress)
{    
    for(int i = 0; i<receivers.matrix.size(); i++){
        if(progress.wasCanceled()){
            return false;
        }
        for(auto currentReceiver : receivers.matrix.at(i)){
            for(auto currentSource : pointSources){
                NoiseEngine::P2P(currentSource, currentReceiver);
            }

        }
        progress.setValue(i);
        qApp->processEvents();
    }
    return true;
}






bool MainWindow::eventFilter(QObject *target, QEvent *event)
{

    if(target == &scene){        
        QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (sceneEvent->type() == QEvent::GraphicsSceneMouseMove)
          {
            QString str = QString("x: %1 m, y: %2 m")
                                    .arg(sceneEvent->scenePos().x())
                                    .arg(sceneEvent->scenePos().y());

            statusBar()->showMessage(str);

            movingItemsOnTheScene(sceneEvent->scenePos());

          }


        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["pointSource"])
          {

            PointSource *myPointSource = new PointSource(
                        sceneEvent->scenePos().x(),
                        sceneEvent->scenePos().y(),
                        1.2,90);

            pointSources.push_back(myPointSource);

            // create pixmapItem for the noise source

            QPixmap myPixmap(":/images/icons/point_source.png");
            myPixmap = myPixmap.scaled(16,16,Qt::KeepAspectRatio,Qt::SmoothTransformation);


            PointSourcePixmapItem * myPixmapPointSourceItem = new PointSourcePixmapItem();

            myPixmapPointSourceItem->setPixmap(myPixmap);
            myPixmapPointSourceItem->setPointSource(myPointSource);

            scene.addItem(myPixmapPointSourceItem);

          }



        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){

            /*  Note: scene.mouseGrabberItem() doesn't
                work weel on GraphicsSceneMousePress event but it works well on
                GraphicsSceneMouseRelease event, on the other hand, scene.itemAt()
                doesn't work well on GraphicsSceneMouseRelease because it takes the topmost
                object, but it works well on GraphicsSceneMousePress.
                */


            QGraphicsItem *pressed_item = scene.itemAt(sceneEvent->scenePos(),ui->graphicsView->transform());

            // the next conditional detects if no items or the rasterAreaItem were clicked
            if(pressed_item!=nullptr && pressed_item != &pixmapItem)
            {
                shaded_line = new QGraphicsLineItem;
                p1_shaded_line = sceneEvent->scenePos();
                scene.addItem(shaded_line);
                scene.setShadedItemFlag(true);
            }
        }


        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){

            QGraphicsItem *item_released= scene.mouseGrabberItem();

            // the next conditional when a item(s) that is moving is released in its new position
            if(item_released!=nullptr && item_released != &pixmapItem && scene.getShadedItemFlag())
            {
                item_released->setPos(sceneEvent->scenePos()); // this correct the position to be more acurate
                delete shaded_line;
            }
            scene.setShadedItemFlag(false);
        }


        QGraphicsSceneHoverEvent *sceneEvent2 = static_cast<QGraphicsSceneHoverEvent*>(event);

            if (sceneEvent2->type() == QEvent::GraphicsSceneHoverEnter){
                qDebug()<<sceneEvent2->type();
            }


     return QMainWindow::eventFilter(target, event);
    }
    return false;
}



void MainWindow::on_actionAdd_point_source_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["pointSource"]);

}


void MainWindow::on_actioneditMode_triggered()
{
    ui->graphicsView->setCursor(myCursors["arrowMode"]);

}

void MainWindow::on_actiongrid_triggered()
{
    ui->graphicsView->setCursor(myCursors["gridMode"]);

}

void MainWindow::on_actioncalculateGrid_triggered()
{
    ui->graphicsView->setCursor(myCursors["arrowMode"]);
    resetPixmapArea();
    receivers.resetNoiseReceiver();


    if(pointSources.size() == 0){
        QMessageBox::warning(this, tr("My Application"),
                                       tr("No sources available\n"
                                          "Please enter noise sources"),QMessageBox::Ok);
        return;
    }

    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle(this->windowTitle());
    progress.setLabelText(QObject::tr("Calculating..."));
    progress.setMinimum(0);
    progress.setMaximum(receivers.matrix.size());
    progress.show();

    if(!calculateNoiseFromSources(progress)){
        return;
    }

    progress.setLabelText(QObject::tr("Painting Grid..."));

    receivers.interpolateGrid(); // calculate interpolated receivers
    receivers.paintGrid(*image, myGrid, progress);
    receivers.clearInterpolatedReceivers(); // clean memory

    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));



//    image->save("../test.png", "PNG");
}

void MainWindow::on_actiondrag_mode_triggered()
{
    ui->graphicsView->setCursor(myCursors["dragMode"]);

}

void MainWindow::on_actionzoom_full_triggered()
{
    qreal ofsset = 10;

    QRectF rectF = QRectF(myGrid.getRect().x()-ofsset,
                          myGrid.getRect().y()+ofsset,
                          myGrid.getRect().width()+ofsset,
                          myGrid.getRect().height()+ofsset);

    ui->graphicsView->fitInView(rectF,Qt::KeepAspectRatio);



//        // center scrollbars:

    ui->graphicsView->horizontalScrollBar()->setMaximum(scene.sceneRect().width()*1.1);
    ui->graphicsView->verticalScrollBar()->setMaximum(scene.sceneRect().height()*1.1);


}
