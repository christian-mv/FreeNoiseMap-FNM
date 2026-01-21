#ifndef FNM_UI_QGRAPHICS_SHADED_LINE_ITEM_H
#define FNM_UI_QGRAPHICS_SHADED_LINE_ITEM_H

#include<QGraphicsLineItem>
#include<QFont>


namespace fnm { class SimpleTextItem; }

namespace fnm {

class GraphicsItemShadedLine : public QGraphicsLineItem
{
public:
    GraphicsItemShadedLine();
    QRectF boundingRect() const override;



protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:

    QLineF line1, line2;

    fnm::SimpleTextItem *distanceText;
    fnm::SimpleTextItem *horizontalText;
    fnm::SimpleTextItem *verticalText;
    fnm::SimpleTextItem *degreesText;

    double theta() const;
    void updateShadedLines();
    void drawLines(QPainter *painter) const;

    QString textContainer;


};

}
#endif // MYGRAPHICSSHADEDLINEITEM_H