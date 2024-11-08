#include <initializer_list>
#include <linux/uinput.h>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

class Device {
public:
    Device();
    ~Device();

    void sendEvent(struct input_event controller_event, int type, int code, int value);
    void sendSyncEvent(struct input_event synchronization_event);

private:
    const char* name = "XBOX360 Controller";
    struct uinput_user_dev uidev;
    int device_descriptor = 0;

    int openDescriptor();
    int registerKeymap();
    int fillMetadata();
    int createDevice();
};