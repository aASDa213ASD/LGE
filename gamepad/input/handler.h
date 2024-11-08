#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include <linux/uinput.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <atomic>

class Handler {
public:
    std::atomic<bool> heartbeat = false;
    std::thread thread;

    void togglePause()
    {
        this->is_paused = !is_paused;
    }

protected:
    char device_name[256] = "Unnamed";
    const char* device_path;
    
    struct input_event event;
    int descriptor;
    
    bool is_paused = true;

    virtual void passthrough() {};
    virtual void listen() {};
    virtual void die() {};

    int exposeDescriptor(
        const char* path, char* name, int flags
    );
};

#endif // INPUT_HANDLER