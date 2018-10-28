#ifndef MYGRAPHICSSHADEDLINEITEM_H
#define MYGRAPHICSSHADEDLINEITEM_H

#include<QGraphicsLineItem>
#include<QFont>

class MyGraphicsShadedLineItem : public QGraphicsLineItem
{
public:
    MyGraphicsShadedLineItem();

    QRectF boundingRect() const;



protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:

    int widthOfText;
    QFont font;


};

#endif // MYGRAPHICSSHADEDLINEITEM_H
