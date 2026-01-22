#include "grid_settings.h"

namespace fnm_core {

GridSettings::GridSettings(Rect rect)
{
    GridSettings(); // default parameters
    setRect(rect);
}

unsigned int GridSettings::countRows()
{


    return static_cast<unsigned int>( this->getRect().width / getDeltaX() );
}

unsigned int GridSettings::countColumns()
{
    return static_cast<unsigned int>( this->getRect().height / getDeltaY() );
}

GridSettings::GridSettings()
{
    // grid is 10x10 mt by default
    setDeltaX(10);
    setDeltaY(10);
    setInterpolationFactor(1); // 1 means not interpolated
}

}
