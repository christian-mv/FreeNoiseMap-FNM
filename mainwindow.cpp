#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noise_engine.h"
#include <QDebug>
#include <QDesktopWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myGrid.setRect(QRectF(0, 0, 400, 400));

    myGrid.setDeltaX(5);
    myGrid.setDeltaY(5);
    myGrid.setInterpolationFactor(5);
    receivers.setGrid(myGrid);

    NoiseEngine::addRandomSources(pointSources, myGrid);



    NoiseEngine::calculateNoiseFromSources(&pointSources, &receivers);


    // create and image which its resolution depends on the screen resolution (tested with 1360X768 screen)
    qreal side = qMin(myGrid.getRect().width(), myGrid.getRect().height());
    qreal side2 = qMax(qApp->desktop()->width(), qApp->desktop()->height());




    QImage image(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);


    image.fill(Qt::transparent);

    receivers.paintGrid(image, myGrid);


    image.save("../test.png", "PNG");


    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(image) ));

    pixmapItem.setScale(side/side2); // to represent the real size in the scene


    scene.addItem(&pixmapItem);

    pixmapItem.setPos(myGrid.get_x(), myGrid.get_y());


    scene.setBackgroundBrush(Qt::black);



    ui->graphicsView->setScene(&scene);

//    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom );
    ui->graphicsView->centerOn(QPointF(0,0));
    ui->graphicsView->scale(2,-2); // invert Y axes




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
