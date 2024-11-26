#ifndef RELOADABLE_H
#define RELOADABLE_H

// Function signatures to call from shared object.
typedef void (*Kernel_OnEngineTick)();

struct Reloadable
{
    bool IsValid;

    // This might differ based on the running platform.
    const char* SharedObjectPath;

    // Code references.
    void* SharedObjectCode;
    Kernel_OnEngineTick OnEngineTick;
};

int Reloadable_TryLoadingKernelCode(Reloadable* reloadable);

#endif // RELOADABLE_H
