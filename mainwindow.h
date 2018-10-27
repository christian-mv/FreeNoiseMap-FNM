#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "grid_settings.h"
#include "receivers_grid.h"
#include <mygraphicsscene.h>
#include "myrasterpixmapitemarea.h"
#define VERSION_OF_APP "1.0"
#define MY_APP_NAME "Free Noise Map"


class PointSource;
class PointSourcePixmapItem;
class QProgressDialog;


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

    void on_actiondrag_mode_triggered();

private:
    Ui::MainWindow *ui;
    MyGraphicsScene scene;
    QImage *image;
    MyRasterPixmapItemArea pixmapItem;
    GridSettings myGrid;
    ReceiversGrid receivers;
    vector<PointSource *> pointSources;
    vector<PointSourcePixmapItem *> pixmapPointSources;
    QHash<QString, QCursor> myCursors;
    QImage invertImageOnYAxes(const QImage &image);
    void loadCursors();
    void loadDefaultGrid();
    bool calculateNoiseFromSources(QProgressDialog &progress);
    void resetPixmapArea();
    QLineF *shaded_line; // auxiliary line when dragging items

protected:
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // MAINWINDOW_H
