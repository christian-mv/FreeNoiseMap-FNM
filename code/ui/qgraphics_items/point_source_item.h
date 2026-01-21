#ifndef FNM_QGRAPHICS_ITEM_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_POINT_SOURCE_H

#include "abstract_point_item.h"
namespace fnm_core { class PointSource; }

namespace fnm_ui {

class PointSourceItem : public AbstractPointSourceItem
{
public:
    PointSourceItem();
    void setPointSource(fnm_core::PointSource *source);
    fnm_core::PointSource * getPointSource()const;
    virtual int	type() const override;

};

}
#endif
