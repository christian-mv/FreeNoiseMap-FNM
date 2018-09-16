#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "grid_settings.h"
#include "receivers_grid.h"
#include "pointsource.h"
#include <vector>

// wigget is a temporal class for testing
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);
    void paintRasterOnQimage(QPainter *painter, double zoom=1.0);

private:    
    GridSettings myGrid;
    ReceiversGrid receivers;
    vector<PointSource *> pointSources;
    QImage *image;


};

#endif // WIDGET_H
