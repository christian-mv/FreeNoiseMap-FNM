#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include<QGraphicsScene>

class MyGraphicsScene : public QGraphicsScene
{
public:
    MyGraphicsScene();
    void setShadedItemFlag(bool value); // tell us when the mouse is under click
    bool getShadedItemFlag()const;

protected:
//    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    bool shadedItemFlag = false;

};

#endif // MYGRAPHICSSCENE_H
