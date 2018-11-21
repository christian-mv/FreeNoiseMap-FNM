#include "mainwindow.h"
#include <QApplication>
#include "noise_engine.h"
#include <QtDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include "gradientcolor.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.showMaximized();       

    return a.exec();
}




