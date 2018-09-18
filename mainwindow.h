#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "grid_settings.h"
#include "receivers_grid.h"
#include "pointsource.h"
#include <mygraphicsscene.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyGraphicsScene scene;
    QGraphicsPixmapItem pixmapItem;
    GridSettings myGrid;
    ReceiversGrid receivers;
    vector<PointSource *> pointSources;
    QImage invertImageOnYAxes(const QImage &image);



};

#endif // MAINWINDOW_H
