#include "grid_settings.h"
#include <QDebug>

GridSettings::GridSettings(QRectF rect)
{
    setRect(rect);
}

unsigned int GridSettings::countRows()
{


    return static_cast<unsigned int>( this->getRect().width() / getDeltaX() );
}

unsigned int GridSettings::countColumns()
{
    return static_cast<unsigned int>( this->getRect().height() / getDeltaY() );
}

GridSettings::GridSettings()
{

}
