#ifndef FNM_QGRAPHICS_ITEM_POINT_SOURCE_H
#define FNM_QGRAPHICS_ITEM_POINT_SOURCE_H

#include "fnm_ui_qgraphics_item_abstract_point.h"
class FnmCorePointSource;


class FnmQgraphicsItemPointSource : public FnmQgraphicsItemAbstractPointSource
{
public:
    FnmQgraphicsItemPointSource();
    void setPointSource(FnmCorePointSource *source);
    FnmCorePointSource * getPointSource()const;    
    virtual int	type() const override;

};

#endif
