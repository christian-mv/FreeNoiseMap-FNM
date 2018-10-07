#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent *event);


};

#endif // MYGRAPHICSVIEW_H
