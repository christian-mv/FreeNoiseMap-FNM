#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include<QGraphicsScene>

class MyGraphicsScene : public QGraphicsScene
{
public:
    MyGraphicsScene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // MYGRAPHICSSCENE_H
