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
class SingleLineSource;
class PointSourcePixmapItem;
class MyQGraphicsLineSourcesItem;
class QProgressDialog;
class MyGraphicsShadedLineItem;


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

    void on_actionzoom_full_triggered();

    void on_action_add_line_source_triggered();

private:
    Ui::MainWindow *ui;
    MyGraphicsScene scene;
    QImage *image;
    MyRasterPixmapItemArea pixmapItem;
    GridSettings myGrid;
    ReceiversGrid receivers;
    QHash<QString, QCursor> myCursors;
    QImage invertImageOnYAxes(const QImage &image);
    void loadCursors();
    void loadDefaultGrid();
    bool calculateNoiseFromSources(QProgressDialog &progress);
    void resetPixmapArea();    
    void movingItemsOnTheScene(const QPointF Pos);
    void draggingPointSourceItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent, QGraphicsItem *pressed_item);
    void droppingItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent);
    bool isThereNoiseSources() const;
    bool releaseLineSourceEdition();

    MyGraphicsShadedLineItem *shaded_line; // auxiliary line when dragging items
    QPointF p1_shaded_line; // initial coordinate for shaded_line
    SingleLineSource *singleLineSource = nullptr;
    MyQGraphicsLineSourcesItem *itemLineSources = nullptr;


protected:
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // MAINWINDOW_H
