#ifndef RELOADABLE_H
#define RELOADABLE_H

#include <SDL.h>

// Function signatures to call from shared object.
typedef void (*Kernel_OnEngineRenderScene)(SDL_Renderer* renderer, SDL_Rect rect);

struct Reloadable
{
    bool IsValid;

    // This might differ based on the running platform.
    const char* SharedObjectPath;

    // Code references.
    void* SharedObjectCode;
    Kernel_OnEngineRenderScene OnEngineRenderScene;
};

int Reloadable_TryLoadingSharedObject(Reloadable* reloadable);
void Reloadable_UnloadSharedObject(Reloadable* reloadable);

#endif // RELOADABLE_H
