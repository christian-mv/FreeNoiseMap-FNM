#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "grid_settings.h"
#include "receivers_grid.h"

// wigget is a temporal class for testing
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawMyGrid();
    void drawNoiseCell(QPainter *painter, QColor color, QRectF rect);
    void drawMargin(int dx1=10, int dy1=10, int dx2=10, int dy2=10);
    GridSettings myGrid;
    ReceiversGrid receivers;


};

#endif // WIDGET_H
