<div align="center">
   
   # LGE
   
   **L**inux **G**amepad **E**mulator utility
   
   [![C++](https://img.shields.io/badge/Language-C++-497591?logo=cplusplus&logoColor=fff&style=for-the-badge)](https://en.wikipedia.org/)
   [![LINUX](https://img.shields.io/badge/OS-LINUX-0078a4?logo=quarto&logoColor=fff&style=for-the-badge)](https://en.wikipedia.org/wiki/PHP)
    
</div>

<br>

# About
This project is an older brother of **[WGE]()** written on C++ for Linux operating system called **[LGE]()**.

Project was initially written years ago when I decided to play a very known game that only supports controller inputs and been rewritten to fix some major issues like input lag (thanks python), flexibility in customization and lack of some quality-of-life features like cursor hiding.

# Requirements:
| Prerequisite               | Description                      |
| -------------------------- | -------------------------------- |
| Linux                      | Operating System                 |
| GCC                        | Compiler, tested only on 14.2.1  |
| Keyboard and mouse         | Obviously, right?                |

# Installation:
Step 1: Clone the project by either using git cli
```bash
git clone git@github.com:aASDa213ASD/LGE.git
```
or by downloading the source code directly

Step 2: Build the project with gcc
```bash
cd LGE && ./build.sh
```

Step 3: Launch with root permissions
```bash
cd build/ && sudo gamepad
```
> [!NOTE]  
> Root permissions are required for a reason. Current implementation is not depended on any input library to listen your mouse and keyboard, instead it directly hooks into corresponding file descriptor and detects any action that goes there which on itself requires root permissions to be granted.

# Configuration
All of the tinkering with your binds and gamepad button definitions will be happening in **[SOME_FILE]()** file.

# Usage
Run the executable with root permissions, press your **[pause bind]()** to unpase the gamepad and perhaps press your **[calibration bind]()** to set the origin of right stick to current cursor position.

That's pretty much it, now you can point your gamepad to some program and use it as it was real.
