#pragma once

#include "keys.h"

#include <unordered_map>
#include <vector>

/********************************************************
* The path to the keyboard and mouse                    *
* Run 'sudo libinput list-devices' to see all devices   *
*                                                       *
* /dev/input/event2 -> Example keyboard                 *
* /dev/input/event5 -> Example mouse                    *
*********************************************************/
inline const char* KEYBOARD = "/dev/input/event2";
inline const char* MOUSE = "/dev/input/event20";

/********************************************************
*   - JOYCON_MIN / JOYCON_MAX are both determining      *
*     minimum and maximum values of a stick position.   *
*     Ideally you leave this as is since those values   *
*     are default for most known controllers out there. *
*     Default: -32768 / 32767                           *
*********************************************************/
inline const int JOYCON_MIN = -32768;
inline const int JOYCON_MAX = 32767;

/********************************************************
*   - JOYCON_RIGHT_SENSITIVITY affects two factors      *
*     1. Sensitivity of your mouse movement correlated  *
*     to how fast a stick will reach it's maximum       *
*     or minimum position.                              *
*     2. Deadzone of mouse movement where stick will    *
*     simply not react until you move your mouse        *
*     far enough from origin position.                  *
*     Default: 100                                      *
*********************************************************/
inline const int JOYCON_RIGHT_SENSITIVITY = 100;

/********************************************************
* Custom binds, you are not supposed to change those,   *
* you can add yours and process them accordingly        *
*********************************************************/
inline const int TERMINATE    = 0x1000; // Kill switch
inline const int PAUSE        = 0x1001; // Pause switch
inline const int HALFWAY_MODE = 0x1002; // Left joycon limiter
inline const int HIDE_CURSOR  = 0x1003; // XOrg exclusive
inline const int CALIBRATE    = 0x1004; // Right joycon, mousebind only

/********************************************************
* Special keys are not affected by pause state          *
* therefore they are always working regardless of pause *
*********************************************************/
inline std::unordered_map<int, int> special_keybinds = {
    { KEY_DELETE,       TERMINATE    },
    { KEY_CAPSLOCK,     PAUSE        },
    { KEY_F1,           HIDE_CURSOR  },
    { KEY_RIGHTSHIFT,   HALFWAY_MODE },
};

inline std::unordered_map<int, int> mouse_keybinds = {
    { BTN_SIDE,   CALIBRATE }, // <- Reset right stick origin
    { BTN_LEFT,   BTN_X     },
    { BTN_RIGHT,  BTN_TL2   },
    { BTN_MIDDLE, BTN_TR2   },
};

inline std::unordered_map<int, std::vector<int>> movement_keybinds = {
    { KEY_W, { ABS_Y, JOYCON_MIN } },
    { KEY_A, { ABS_X, JOYCON_MIN } },
    { KEY_S, { ABS_Y, JOYCON_MAX } },
    { KEY_D, { ABS_X, JOYCON_MAX } },
};

inline std::unordered_map<int, int> general_keybinds = {
    { KEY_E,         BTN_B          },
    { KEY_LEFTSHIFT, BTN_A          },
    { KEY_SPACE,     BTN_Y          },
    { KEY_LEFTCTRL,  BTN_THUMBL     },
    { KEY_RIGHTCTRL, BTN_THUMBR     },
    { KEY_LEFTALT,   BTN_START      },
    { KEY_M,         BTN_SELECT     },
    { KEY_Q,         BTN_TL         },
    { KEY_R,         BTN_TR         },
    { KEY_Z,         BTN_DPAD_UP    },
    { KEY_X,         BTN_DPAD_DOWN  },
    { KEY_C,         BTN_DPAD_LEFT  },
    { KEY_V,         BTN_DPAD_RIGHT },
};