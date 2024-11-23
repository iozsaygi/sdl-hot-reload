#include "Debugger.h"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>

void Debugger_Log(const char* message, ...)
{
    assert(message != nullptr && strlen(message) > 0);

    va_list args;
    va_start(args, message);

    vprintf(message, args);
    printf("\n");

    va_end(args);
}
