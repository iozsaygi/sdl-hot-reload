#include "Reloadable.h"
#include <SDL_loadso.h>
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
    reloadable->OnEngineTick =
        Kernel_OnEngineTick(SDL_LoadFunction(reloadable->SharedObjectCode, "Kernel_OnEngineTick"));

    if (reloadable->OnEngineTick == nullptr)
    {
        Debugger_Log("Failed to load function from shared object, the reason was: %s", SDL_GetError());
        return -1;
    }

    reloadable->IsValid = true;

    return 0;
}

void Reloadable_UnloadSharedObject(Reloadable* reloadable)
{
    assert(reloadable != nullptr);

    if (reloadable->SharedObjectCode != nullptr)
    {
        SDL_UnloadObject(reloadable->SharedObjectCode);
        reloadable->SharedObjectCode = nullptr;
    }

    reloadable->IsValid = false;
    reloadable->OnEngineTick = nullptr;
}
