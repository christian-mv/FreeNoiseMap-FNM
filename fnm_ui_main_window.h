#ifndef FNM_UI_MAIN_WINDOW_H
#define FNM_UI_MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "fnm_core_grid_settings.h"
#include "fnm_ui_receivers_grid.h"
#include "fnm_ui_qgraphics_item_raster_pixmap_area.h"


class FnmCorePointSource;
class FnmCoreBarrierSegment;
class FnmQgraphicsItemPolyLine;
class QLineF;
class FnmGraphicsItemMultiLineSource;
class FnmQgraphicsItemPointSource;
class FnmQGraphicsItemBarrier;
class QProgressDialog;
class FnmGraphicsItemShadedLine;
class QActionGroup;

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

    void on_actionAcoustic_Barrier_triggered();

    void on_actionadd_polyline_triggered();

    void on_actionAdd_Receiver_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QImage *image;
    FnmQgraphicsItemRasterPixmap pixmapItem;
    FnmCoreGridSettings myGrid;
    FnmReceiversGrid receivers;
    QHash<QString, QCursor> myCursors;
    QActionGroup *menuActionsGroup; // used to make the grapic menu mutually exclusive
    QImage invertImageOnYAxes(const QImage &image);
    void loadCursors();
    void makeMenuMutualExclusive();
    void loadDefaultGrid();
    bool calculateNoiseFromSources(QProgressDialog &progress);
    QList<FnmQGraphicsItemBarrier *> barrierList() const; // returns all barriers from the scene
    std::vector<FnmCoreBarrierSegment*> barrierSegmentsToStdVector() const;
    void resetPixmapArea();
    void movingItemsOnTheScene(const QGraphicsSceneMouseEvent *sceneMouseEvent);
    void updateShadedLinesItem(QPointF pos);
    void createShadedLinesItem(QPointF pos);
    void deleteShadedLinesItem();
    void droppingItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent);
    bool isThereNoiseSources() const;
    void releaseLineItemEdition();


    FnmGraphicsItemShadedLine *shaded_line = nullptr; // auxiliary line when dragging items
    QPointF p1_shaded_line; // initial coordinate for shaded_line

    QLineF *singleLine;
    FnmQgraphicsItemPolyLine *polyLine;
    FnmGraphicsItemMultiLineSource *multiLineSource;
    FnmQGraphicsItemBarrier *acousticBarrier;


protected:
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // MAINWINDOW_H
