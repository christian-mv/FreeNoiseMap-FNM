#ifndef MYGRAPHICSSHADEDLINEITEM_H
#define MYGRAPHICSSHADEDLINEITEM_H

#include<QGraphicsLineItem>
#include<QFont>
#include "myqgraphicssimpletextitem.h"

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

    QLineF line1, line2;
    MyQGraphicsSimpleTextItem *distanceText;
    MyQGraphicsSimpleTextItem *horizontalText;
    MyQGraphicsSimpleTextItem *verticalText;
    double theta() const;
    void updateShadedLines();
    void drawLines(QPainter *painter) const;
    void drawText();
    void updateWidOfText(const QPainter *p);
    int widthOfText;
    QFont myFont;
    QString textContainer;


};

#endif // MYGRAPHICSSHADEDLINEITEM_H
