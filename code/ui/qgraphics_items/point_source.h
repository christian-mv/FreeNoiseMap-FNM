#ifndef FNM_QGRAPHICS_ITEM_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_POINT_SOURCE_H

#include "abstract_point.h"
namespace fnm_core { class CorePointSource; }

namespace fnm_ui {

class PointSource : public AbstractPointSource
{
public:
    PointSource();
    void setPointSource(fnm_core::CorePointSource *source);
    fnm_core::CorePointSource * getPointSource()const;
    virtual int	type() const override;

};

}
#endif
