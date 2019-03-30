#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "grid_settings.h"
#include "receivers_grid.h"
#include "myrasterpixmapitemarea.h"



class MinimalPointSource;
class QLineF;
class QGraphicsPolyLineSourceItem;
class PointSourcePixmapItem;
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
    QGraphicsScene scene;
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
    void movingItemsOnTheScene(const QGraphicsSceneMouseEvent *sceneMouseEvent);
    void updateShadedLinesItem(QPointF pos);
    void createShadedLinesItem(QPointF pos);
    void deleteShadedLinesItem();
    void droppingItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent);
    bool isThereNoiseSources() const;
    void releaseLineSourceEdition();


    MyGraphicsShadedLineItem *shaded_line = nullptr; // auxiliary line when dragging items
    QPointF p1_shaded_line; // initial coordinate for shaded_line

    QLineF *singleLine;
    QGraphicsPolyLineSourceItem * polyLineSource;


protected:
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // MAINWINDOW_H
