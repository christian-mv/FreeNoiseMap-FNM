#include "mygraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

MyGraphicsScene::MyGraphicsScene()
{

}



void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<mouseEvent->scenePos();
}
