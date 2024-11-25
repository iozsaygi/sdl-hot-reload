#ifndef RELOADABLE_H
#define RELOADABLE_H

// Function signatures to call from shared object.
typedef void (*Kernel_OnEngineTick)();

struct Reloadable
{
public:
    bool IsValid;

    // This might differ based on the running platform.
    const char* SharedObjectPath;

    // Function references.
    Kernel_OnEngineTick OnEngineTick;
};

#endif // RELOADABLE_H
