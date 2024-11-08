#include "xorg.h"
#include "../common/log.h"

XOrg::XOrg()
{
    log("Instantiating XOrg wrapper ... ");
    this->display = XOpenDisplay(NULL);
    printf("OK \n");
}

XOrg::~XOrg()
{
    log("Destroying XOrg wrapper ... ");
    
    if (this->is_cursor_hidden)
    {
        this->showCursor();
    }
    
    XCloseDisplay(this->display);
    
    printf("OK \n");
}

void XOrg::switchCursorVisibility()
{
    if (this->is_cursor_hidden)
    {
        this->showCursor();
    }
    else
    {
        this->hideCursor();
    }
}

void XOrg::hideCursor()
{
    XFixesHideCursor(display, DefaultRootWindow(display));
    XFlush(display);
    this->is_cursor_hidden = true;
}

void XOrg::showCursor()
{
    XFixesShowCursor(display, DefaultRootWindow(display));
    XFlush(display);
    this->is_cursor_hidden = false;
}