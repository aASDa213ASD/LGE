#include "left.h"

void LeftJoycon::setAxis(int x, int y)
{
    if (this->half_mode)
    {
        x /= 2;
        y /= 2;
    }

    this->axis[0] = clamp(x);
    this->axis[1] = clamp(y);
}

void LeftJoycon::switchHalfMode()
{
    this->half_mode = !this->half_mode;
}