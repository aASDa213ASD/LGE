#include <unistd.h>
#include <stdio.h>

#include "gamepad/core/controller.h"

bool is_super_user()
{
    if (!getuid())
    {
        return true;
    }

    return false;
}

int main()
{
    if (!is_super_user())
    {
        printf("Not enough permission, are you root?\n");
        return 1;
    }

    Controller gamepad = Controller();
    gamepad.heartbeat();
    
    return 0;
}

