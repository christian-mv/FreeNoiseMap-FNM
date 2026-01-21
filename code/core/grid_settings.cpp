#include "grid_settings.h"
#include <QDebug>

namespace fnm_core {

CoreGridSettings::CoreGridSettings(QRectF rect)
{
    CoreGridSettings(); // default parameters
    setRect(rect);
}

unsigned int CoreGridSettings::countRows()
{


    return static_cast<unsigned int>( this->getRect().width() / getDeltaX() );
}

unsigned int CoreGridSettings::countColumns()
{
    return static_cast<unsigned int>( this->getRect().height() / getDeltaY() );
}

CoreGridSettings::CoreGridSettings()
{
    // grid is 10x10 mt by default
    setDeltaX(10);
    setDeltaY(10);
    setInterpolationFactor(1); // 1 means not interpolated
}

}
