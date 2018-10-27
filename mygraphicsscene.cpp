#include "mygraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>


MyGraphicsScene::MyGraphicsScene()
{

}

void MyGraphicsScene::setShadedItemFlag(bool value)
{
    shadedItemFlag = value;
}

bool MyGraphicsScene::getShadedItemFlag() const
{
    return shadedItemFlag;
}

//void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    QString string = QString("%1, %2")
//                            .arg(event->scenePos().x())
//                            .arg(event->scenePos().y()); //Update the cursor potion text

//        qDebug()<<string;
//}





