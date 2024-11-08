#include "controller.h"

#include "../../common/settings.h"

#include <stdio.h>

Controller::Controller()
{

}

Controller::~Controller()
{
    
}

void Controller::heartbeat()
{
    this->keyboard->listen();
    this->mouse->listen();

    if (this->keyboard->thread.joinable())
    {
        this->keyboard->thread.join();
    }

    if (this->mouse->thread.joinable())
    {
        this->mouse->thread.join();
    }
}

void Controller::onMouseMove(int event_code, int value)
{
    if (this->is_paused)
    {
        return;
    }

    if (event_code == REL_X)
    {
        this->right_joycon.setPosition(value);
        this->device.sendEvent(
            this->controller_event,
            EV_ABS, ABS_RX, this->right_joycon.axis[0]
        );
    }
    else if (event_code == REL_Y)
    {
        this->right_joycon.setPosition(0, value);
        this->device.sendEvent(
            this->controller_event,
            EV_ABS, ABS_RY, this->right_joycon.axis[1]
        );
    }

    this->device.sendSyncEvent(this->controller_event);
}

void Controller::onMousePress(int event_code, int value)
{
    if (this->is_paused)
    {
        return;
    }

    auto mouse_button = mouse_keybinds.find(event_code);
    if (mouse_button != mouse_keybinds.end())
    {
        switch (mouse_button->second)
        {
            case CALIBRATE:
            {
                this->right_joycon.calibrate();
                this->device.sendEvent(
                    this->controller_event,
                    EV_ABS, ABS_RX, this->right_joycon.axis[0]
                );
                this->device.sendEvent(
                    this->controller_event,
                    EV_ABS, ABS_RY, this->right_joycon.axis[1]
                );
                this->device.sendSyncEvent(this->controller_event);
                break;
            }
            
            default:
            {
                this->device.sendEvent(
                    this->controller_event,
                    EV_KEY, mouse_button->second, value
                );
                this->device.sendSyncEvent(this->controller_event);
                break;
            }
        }
    }
}

void Controller::onKeyPress(int key_code, int value)
{
    auto special_key = special_keybinds.find(key_code);
    if (special_key != special_keybinds.end() && value != 1)
    {
        switch(special_key->second)
        {
            case TERMINATE:
            {
                this->keyboard->die();
                this->mouse->die();
                break;
            }
            
            case PAUSE:
            {
                this->keyboard->togglePause();
                this->mouse->togglePause();
                this->togglePause();
                break;
            }

            case HIDE_CURSOR:
            {
                this->xorg.switchCursorVisibility();
                break;
            }

            case HALFWAY_MODE:
            {
                this->left_joycon.switchHalfMode();
                break;
            }
        }
    }

    if (this->is_paused)
    {
        return;
    }

    auto movement_key = movement_keybinds.find(key_code);
    if (movement_key != movement_keybinds.end())
    {
        if (movement_key->second[0] == ABS_X)
        {
            this->left_joycon.setAxis(
                value != 0 ? movement_key->second[1] : 0, 0
            );
            this->device.sendEvent(
                this->controller_event, EV_ABS,
                movement_key->second[0], this->left_joycon.axis[0]
            );
        }
        else if (movement_key->second[0] == ABS_Y)
        {
            this->left_joycon.setAxis(
                0, value != 0 ? movement_key->second[1] : 0
            );
            this->device.sendEvent(
                this->controller_event, EV_ABS,
                movement_key->second[0], this->left_joycon.axis[1]
            );
        }

        this->device.sendSyncEvent(this->controller_event);
    }

    auto general_key = general_keybinds.find(key_code);
    if (general_key != general_keybinds.end())
    {
        this->device.sendEvent(
            this->controller_event, EV_KEY,
            general_key->second, value 
        );
        this->device.sendSyncEvent(this->controller_event);
    }
}

void Controller::togglePause()
{
    this->is_paused = !is_paused;
}
