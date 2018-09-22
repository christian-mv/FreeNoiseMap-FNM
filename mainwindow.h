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

private slots:
    void on_actionAdd_point_source_triggered();
    void on_actioneditMode_triggered();
    void on_actiongrid_triggered();
    void on_actioncalculateGrid_triggered();

private:
    Ui::MainWindow *ui;
    MyGraphicsScene scene;
    QImage *image;
    QGraphicsPixmapItem pixmapItem;
    GridSettings myGrid;
    ReceiversGrid receivers;
    vector<PointSource *> pointSources;
    QImage invertImageOnYAxes(const QImage &image);
    QHash<QString, QCursor> myCursors;
    void loadCursors();
    void loadDefaultGrid();
    bool calculateNoiseFromSources();


protected:
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // MAINWINDOW_H
