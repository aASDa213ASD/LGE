#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

inline void log(const char* format, ...)
{
    char buffer[256];
    struct tm* tm_info;
    time_t now = time(0);
    tm_info = localtime(&now);

    strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);

    fprintf(stdout, "[%s] ", buffer);

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fflush(stdout);
}
