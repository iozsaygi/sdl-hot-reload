#include "Reloadable.h"
#include <SDL.h>
#include <cassert>
#include "Debugger.h"

bool Reloadable_Prepare(const Reloadable* reloadable)
{
    assert(reloadable != nullptr);

    SDL_RWops* mainInstance = SDL_RWFromFile(reloadable->SharedObjectPath, "r");
    SDL_RWops* duplicateInstance = SDL_RWFromFile(reloadable->TemporarySharedObjectPath, "w");

    const Sint64 size = SDL_RWsize(mainInstance);

    // ReSharper disable once CppDFAMemoryLeak
    void* buffer = SDL_calloc(1, size);
    SDL_RWread(mainInstance, buffer, size, 1);

    // Write buffer to target
    SDL_RWwrite(duplicateInstance, buffer, size, 1);

    Debugger_Log("Successfully copied shared object.");

    SDL_RWclose(mainInstance);
    SDL_RWclose(duplicateInstance);
    SDL_free(buffer);

    return true;
}

int Reloadable_TryLoadingSharedObject(Reloadable* reloadable)
{
    assert(reloadable != nullptr);
    assert(Reloadable_Prepare(reloadable));

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
