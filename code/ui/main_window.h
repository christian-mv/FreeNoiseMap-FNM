#ifndef FNM_UI_MAIN_WINDOW_H
#define FNM_UI_MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "grid_settings.h"
#include "receivers_grid.h"
#include "qgraphics_items/raster_pixmap_area_item.h"
#include <QActionGroup>
#include "noise_grid.h" // Include NoiseGrid

// Widgets
class QAction;
class QWidget;
class QHBoxLayout;
class QMenuBar;
class QStatusBar;
class QToolBar;
namespace fnm_ui { class FnmView; }

namespace fnm_core {
class PointSource;
class BarrierSegment;
}

namespace fnm_ui {
class PolyLineItem;
class MultiLineSourceItem;
class PointSourceItem;
class BarrierItem;
class ShadedLineItem;
class RasterPixmapItem;
}

class QLineF;
class QProgressDialog;

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
    void setupUI();

    // UI Elements
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    fnm_ui::FnmView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    // Actions
    QAction *actionAdd_point_source;
    QAction *actioneditMode;
    QAction *actiongrid;
    QAction *actioncalculateGrid;
    QAction *actiondrag_mode;
    QAction *actionzoom_full;
    QAction *action_add_line_source;
    QAction *actionAcoustic_Barrier;
    QAction *actionadd_polyline;
    QAction *actionAdd_Receiver;

    QGraphicsScene scene;
    QImage *image;
    fnm_ui::RasterPixmapItem pixmapItem;
    fnm_core::NoiseGrid noiseGridModel;
    fnm_ui::ReceiversGrid receivers;
    QHash<QString, QCursor> myCursors;
    QActionGroup *menuActionsGroup; // used to make the grapic menu mutually exclusive
    QImage invertImageOnYAxes(const QImage &image);
    void loadCursors();
    void makeMenuMutualExclusive();
    void loadDefaultGrid();
    bool calculateNoiseFromSources(QProgressDialog &progress);
    QList<fnm_ui::BarrierItem *> barrierList() const; // returns all barriers from the scene
    std::vector<fnm_core::BarrierSegment*> barrierSegmentsToStdVector() const;
    void resetPixmapArea();
    void movingItemsOnTheScene(const QGraphicsSceneMouseEvent *sceneMouseEvent);
    void updateShadedLinesItem(QPointF pos);
    void createShadedLinesItem(QPointF pos);
    void deleteShadedLinesItem();
    void droppingItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent);
    bool isThereNoiseSources() const;
    void releaseLineItemEdition();


    fnm_ui::ShadedLineItem *shaded_line = nullptr; // auxiliary line when dragging items
    QPointF p1_shaded_line; // initial coordinate for shaded_line

    QLineF *singleLine;
    fnm_ui::PolyLineItem *polyLine;
    fnm_ui::MultiLineSourceItem *multiLineSource;
    fnm_ui::BarrierItem *acousticBarrier;


protected:
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // MAINWINDOW_H
