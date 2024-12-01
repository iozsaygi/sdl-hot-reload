#ifndef RELOADABLE_H
#define RELOADABLE_H

// Function signatures to call from shared object.
typedef void (*Kernel_OnEngineTick)();

struct Reloadable
{
    bool IsValid;

    // This might differ based on the running platform.
    const char* SharedObjectPath;

    // This is temporary path to copy the shared object whenever reload requested.
    const char* TemporarySharedObjectPath;

    // Code references.
    void* SharedObjectCode;
    Kernel_OnEngineTick OnEngineTick;
};

int Reloadable_TryLoadingSharedObject(Reloadable* reloadable);
void Reloadable_UnloadSharedObject(Reloadable* reloadable);

#endif // RELOADABLE_H
