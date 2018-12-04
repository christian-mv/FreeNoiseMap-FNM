#include "my_qgraphics_line_sources_item.h"
#include "single_line_source.h"
#include <QDebug>


MyQGraphicsLineSourcesItem::MyQGraphicsLineSourcesItem(QGraphicsItem *parent,
                                                       QPointF startPoint)
    : QGraphicsPathItem(parent)
{
    path.moveTo(startPoint);

}

void MyQGraphicsLineSourcesItem::addSource(SingleLineSource *source)
{

    vectorLineSources.push_back(source);
    path.lineTo(source->get_x2(), source->get_y2());
    setPath(path);
}

int MyQGraphicsLineSourcesItem::countSources() const
{
    return vectorLineSources.size();
}



const std::vector<SingleLineSource *> MyQGraphicsLineSourcesItem::getLineSources() const
{
    return this->vectorLineSources;
}


