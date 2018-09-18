#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // MYGRAPHICSVIEW_H
