#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xfixes.h>

class XOrg {
public:
    XOrg();
    ~XOrg();
    void switchCursorVisibility();
    void hideCursor();
    void showCursor();

private:
    Display* display;
    bool is_cursor_hidden = false;
};