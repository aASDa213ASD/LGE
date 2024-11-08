#include "keyboard.h"

#include "../../common/log.h"
#include "../../common/settings.h"

KeyboardHandler::KeyboardHandler(onKeyPress onPress)
{
    log("Intercepting keyboard ... ");
    
    this->onPress = onPress;
    this->device_path = KEYBOARD;
    
    this->descriptor = exposeDescriptor(
        this->device_path, this->device_name, O_RDWR | O_NOCTTY | O_NONBLOCK
    );

    if (this->descriptor == 0)
    {
        printf("FAIL // KEYBOARD_DESCRIPTOR\n");
        return;
    }

    printf("%s, OK\n", this->device_name);
}

KeyboardHandler::~KeyboardHandler()
{
    log("Killing keyboard listener ... ");
    
    if (this->descriptor != 0)
    {
        close(this->descriptor);
        this->descriptor = 0;
    }

    printf("OK \n");
}

void KeyboardHandler::passthrough()
{
    while (this->heartbeat)
    {
        if (this->is_paused)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }

        if (read(this->descriptor, &this->event, sizeof(this->event)) == -1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }

        if (event.type == EV_KEY)
        {
            this->onPress(event.code, event.value);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void KeyboardHandler::listen()
{
    this->heartbeat = true;

    this->thread = std::thread(
        &KeyboardHandler::passthrough, this
    );
}

void KeyboardHandler::die()
{
    this->heartbeat = false;
}