#include "device.h"
#include "../../common/log.h"
#include "../../common/keys.h"

Device::Device()
{
    log("Creating a virtual device ... ");
    
    if (this->openDescriptor() < 0)
    {
        printf("FAIL // UINPUT\n");
        return;
    }

    if (this->registerKeymap() < 0)
    {
        printf("FAIL // REGISTER_KEYMAP\n");
        return;
    }
    
    if (this->fillMetadata() < 0)
    {
        printf("FAIL // FILL_METADATA\n");
        return;
    }

    if (this->createDevice() < 0)
    {
        printf("FAIL // UI_DEV_CREATE\n");
        return;
    }

    printf("OK \n");
}

Device::~Device()
{
    log("Destroying a virtual device ... ");

    if (this->device_descriptor != 0)
    {
        close(this->device_descriptor);
        this->device_descriptor = 0;
    }

    printf("OK \n");
}

void Device::sendEvent(struct input_event event, int type, int code, int value)
{
    memset(&event, 0, sizeof(struct input_event));
    event.type  = type;
    event.code  = code;
    event.value = value;

    if(write(this->device_descriptor, &event, sizeof(struct input_event)) < 0)
    {
        log("ERROR: Couldn't write event to device\n");
    }
}

void Device::sendSyncEvent(struct input_event synchronization_event)
{
    memset(&synchronization_event, 0, sizeof(struct input_event));
    synchronization_event.type  = EV_SYN;
    synchronization_event.code  = 0;
    synchronization_event.value = 0;

    if(write(this->device_descriptor, &synchronization_event, sizeof(struct input_event)) < 0)
    {
        log("ERROR: Couldn't write synchronization event to device\n");
    }
}

int Device::openDescriptor()
{
    this->device_descriptor = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    
    if (this->device_descriptor < 0)
    {
        return -1;
    }

    return 0;
}

int Device::registerKeymap()
{
    ioctl(this->device_descriptor, UI_SET_EVBIT, EV_KEY);
    
    for (int key : {
        BTN_A, BTN_B, BTN_X, BTN_Y, BTN_TL, BTN_TR, BTN_TL2, BTN_TR2,
        BTN_START, BTN_SELECT, BTN_THUMBL, BTN_THUMBR, BTN_DPAD_UP,
        BTN_DPAD_DOWN, BTN_DPAD_LEFT, BTN_DPAD_RIGHT
    })
    {
        ioctl(this->device_descriptor, UI_SET_KEYBIT, key);
    }

    ioctl(this->device_descriptor, UI_SET_EVBIT, EV_ABS);
    
    for (int abs_key : {
        ABS_X, ABS_Y, ABS_RX, ABS_RY, ABS_TILT_X, ABS_TILT_Y
    })
    {
        ioctl(this->device_descriptor, UI_SET_ABSBIT, abs_key);
        uidev.absmax[abs_key] = abs_key == ABS_X || abs_key == ABS_Y ? 32767 : 512;
        uidev.absmin[abs_key] = abs_key == ABS_X || abs_key == ABS_Y ? -32768 : -512;
        uidev.absfuzz[abs_key] = 0; // Noise tolerance to the axis
        uidev.absflat[abs_key] = 0; // Dead zone to the axis
    }

    return 0;
}

int Device::fillMetadata()
{
    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, this->name);

    uidev.id.bustype = BUS_USB;
    uidev.id.vendor = 0x3;
    uidev.id.product = 0x3;
    uidev.id.version = 2;

    return 0;
}

int Device::createDevice()
{
    if (
        write(this->device_descriptor, &uidev, sizeof(uidev)) < 0 ||
        ioctl(this->device_descriptor, UI_DEV_CREATE) < 0
    )
    {
        return -1;
    }

    return 0;
}