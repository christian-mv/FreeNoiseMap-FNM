#include "fnm_core_grid_settings.h"
#include <QDebug>

FnmCoreGridSettings::FnmCoreGridSettings(QRectF rect)
{
    FnmCoreGridSettings(); // default parameters
    setRect(rect);
}

unsigned int FnmCoreGridSettings::countRows()
{


    return static_cast<unsigned int>( this->getRect().width() / getDeltaX() );
}

unsigned int FnmCoreGridSettings::countColumns()
{
    return static_cast<unsigned int>( this->getRect().height() / getDeltaY() );
}

FnmCoreGridSettings::FnmCoreGridSettings()
{
    // grid is 10x10 mt by default
    setDeltaX(10);
    setDeltaY(10);
    setInterpolationFactor(1); // 1 means not interpolated
}
