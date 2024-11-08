#include "mouse.h"

#include "../../common/log.h"
#include "../../common/settings.h"

MouseHandler::MouseHandler(onMouseMove onMove, onMouseClick onClick)
{
    log("Intercepting mouse ... ");
    
    this->onMove = onMove;
    this->onClick = onClick;
    this->device_path = MOUSE;

    this->descriptor = exposeDescriptor(
        this->device_path, this->device_name, O_RDWR | O_NOCTTY | O_NONBLOCK
    );

    if (this->descriptor == 0)
    {
        printf("FAIL // MOUSE_DESCRIPTOR\n");
        return;
    }

    printf("%s, OK\n", this->device_name);
}

MouseHandler::~MouseHandler()
{
    log("Killing mouse listener ... ");
    
    if (this->descriptor != 0)
    {
        close(this->descriptor);
        this->descriptor = 0;
    }

    printf("OK \n");
}

void MouseHandler::passthrough()
{
    while (this->heartbeat)
    {
        if (this->is_paused)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        
        if (read(this->descriptor, &this->event, sizeof(this->event)) == -1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }
        
        if (event.type == EV_REL)
        {
            this->onMove(event.code, event.value);
        }
        else if (event.type == EV_KEY)
        {
            this->onClick(event.code, event.value);
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(250000));
    }
}

void MouseHandler::listen()
{
    this->heartbeat = true;

    this->thread = std::thread(
        &MouseHandler::passthrough, this
    );
}

void MouseHandler::die()
{
    this->heartbeat = false;
}