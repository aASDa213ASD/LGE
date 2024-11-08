#include "handler.h"

int Handler::exposeDescriptor(const char* path, char* name, int flags)
{
    int file_descriptor = open(path, flags);
    
    if (file_descriptor == -1)
    {
        return 0;
    }

    if (ioctl(file_descriptor, EVIOCGNAME(*name), name) == -1)
    {
        return 0;
    }

    return file_descriptor;
}