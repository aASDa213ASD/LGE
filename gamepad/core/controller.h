#include "../../xorg/xorg.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../joycons/left.h"
#include "../joycons/right.h"
#include "device.h"

#include <linux/uinput.h>
#include <linux/input.h>
#include <memory>

class Controller {
public:
    Controller();
    ~Controller();

    void heartbeat();
    void togglePause();
    
    void onKeyPress(int key_code, int value); // Maybe should be private
    void onMouseMove(int event_code, int value);
    void onMousePress(int event_code, int value);

private:
    bool is_paused = true;
    struct input_event controller_event;

    XOrg xorg;
    Device device;
    LeftJoycon left_joycon;
    RightJoycon right_joycon;
    
    std::unique_ptr<KeyboardHandler> keyboard = std::make_unique<KeyboardHandler>(
        [this](int key_code, int value) { this->onKeyPress(key_code, value); }
    );

    std::unique_ptr<MouseHandler> mouse = std::make_unique<MouseHandler>(
        [this](int event_code, int value) { this->onMouseMove(event_code, value);  },
        [this](int event_code, int value) { this->onMousePress(event_code, value); }
    );
};