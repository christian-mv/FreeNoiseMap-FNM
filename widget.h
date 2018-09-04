#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QRectF>
#include "grid_settings.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    GridSettings noiseGridSettings;
    void drawMyGrid();
    void drawNoiseCell(QPainter *painter, QColor color, QRectF rect);
    void drawMargin(int dx1=10, int dy1=10, int dx2=10, int dy2=10);
};

#endif // WIDGET_H
