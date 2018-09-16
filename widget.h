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
    void setImage( QImage *image){this->image = image; this->update();}

protected:
    void paintEvent(QPaintEvent *event);


private:    

    QImage *image;


};

#endif // WIDGET_H
