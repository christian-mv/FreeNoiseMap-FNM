#ifndef FNM_QGRAPHICS_ITEM_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_POINT_SOURCE_H

#include "abstract_point.h"
namespace fnm_core { class PointSource; }

namespace fnm_ui {

class PointSource : public AbstractPointSource
{
public:
    PointSource();
    void setPointSource(fnm_core::PointSource *source);
    fnm_core::PointSource * getPointSource()const;
    virtual int	type() const override;

};

}
#endif
