#include "right.h"

#include "../../common/settings.h"

RightJoycon::RightJoycon()
{
    this->sensitivity = JOYCON_RIGHT_SENSITIVITY;
}

void RightJoycon::setPosition(int x, int y)
{
    if (x != 0)
    {
        this->axis[0] += (x - this->origin[0]) * this->sensitivity;
        this->axis[0] = clamp(this->axis[0]);
    }

    if (y != 0)
    {
        this->axis[1] += (y - this->origin[1]) * this->sensitivity;
        this->axis[1] = clamp(this->axis[1]);
    }
}

void RightJoycon::calibrate()
{
    this->axis = { 0, 0 };
    this->reset();
}
