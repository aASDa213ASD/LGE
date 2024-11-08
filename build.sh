g++ -std=c++23                      \
    xorg/xorg.cpp                   \
    gamepad/joycons/left.cpp        \
    gamepad/joycons/right.cpp       \
    gamepad/input/handler.cpp	    \
    gamepad/input/keyboard.cpp	    \
    gamepad/input/mouse.cpp	    \
    gamepad/core/device.cpp         \
    gamepad/core/controller.cpp     \
    main.cpp                        \
    -lX11 -lXfixes -o build/gamepad
