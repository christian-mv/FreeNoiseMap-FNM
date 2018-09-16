#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noise_engine.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myGrid.setRect(QRectF(50, 50, 200, 200));

    myGrid.setDeltaX(10);
    myGrid.setDeltaY(10);
    myGrid.setInterpolationFactor(5);
    receivers.setGrid(myGrid);

    NoiseEngine::addRandomSources(pointSources, myGrid);



    NoiseEngine::calculateNoiseFromSources(&pointSources, &receivers);


    qDebug()<<myGrid.getRect().width();
    qreal side = qMin(myGrid.getRect().width(), myGrid.getRect().height());
    qreal side2 = qMax(width(), height());




    QImage image(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);

    image.fill(Qt::transparent);

    receivers.paintGrid(image, myGrid);


    image.save("../test.png", "PNG");

    pixmapItem.setPixmap(QPixmap::fromImage(image));
    scene.addItem(&pixmapItem);
    pixmapItem.setPos(0,0);
    scene.setSceneRect(pixmapItem.boundingRect());
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
