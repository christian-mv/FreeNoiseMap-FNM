#ifndef FNM_UI_QGRAPHICS_SHADED_LINE_ITEM_H
#define FNM_UI_QGRAPHICS_SHADED_LINE_ITEM_H

#include<QGraphicsLineItem>
#include<QFont>


namespace fnm_ui { class SimpleTextItem; }

namespace fnm_ui {

class ShadedLineItem : public QGraphicsLineItem
{
public:
    ShadedLineItem();
    QRectF boundingRect() const override;



protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:

    QLineF line1, line2;

    fnm_ui::SimpleTextItem *distanceText;
    fnm_ui::SimpleTextItem *horizontalText;
    fnm_ui::SimpleTextItem *verticalText;
    fnm_ui::SimpleTextItem *degreesText;

    double theta() const;
    void updateShadedLines();
    void drawLines(QPainter *painter) const;

    QString textContainer;


};

}
#endif // MYGRAPHICSSHADEDLINEITEM_H
