#include "Reloadable.h"
#include <SDL.h>
#include <cassert>
#include "Debugger.h"

int Reloadable_TryLoadingSharedObject(Reloadable* reloadable)
{
    assert(reloadable != nullptr);

    reloadable->SharedObjectCode = SDL_LoadObject(reloadable->SharedObjectPath);

    if (reloadable->SharedObjectCode == nullptr)
    {
        Debugger_Log("Failed to load shared object, the reason was: %s", SDL_GetError());
        return -1;
    }

    // ReSharper disable once CppFunctionalStyleCast
    reloadable->OnEngineRenderScene =
        Kernel_OnEngineRenderScene(SDL_LoadFunction(reloadable->SharedObjectCode, "Kernel_OnEngineRenderScene"));

    if (reloadable->OnEngineRenderScene == nullptr)
    {
        Debugger_Log("Failed to load function from shared object, the reason was: %s", SDL_GetError());
        return -1;
    }

    reloadable->IsValid = true;
    Debugger_Log("Successfully loaded shared object.");

    return 0;
}

void Reloadable_UnloadSharedObject(Reloadable* reloadable)
{
    assert(reloadable != nullptr);

    if (reloadable->SharedObjectCode != nullptr)
    {
        SDL_UnloadObject(reloadable->SharedObjectCode);
        reloadable->SharedObjectCode = nullptr;

        Debugger_Log("Unloaded the shared object instance.");
    }

    reloadable->IsValid = false;
    reloadable->OnEngineRenderScene = nullptr;
}
