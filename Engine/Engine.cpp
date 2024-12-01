#include "Engine.h"
#include <cassert>
#include <cstring>
#include "Debugger.h"

int Engine_Initialize(const int width, const int height, const char* title, EngineEntry* engineEntry)
{
    assert(width > 0);
    assert(height > 0);
    assert(title != nullptr && strlen(title) > 0);
    assert(engineEntry != nullptr);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Debugger_Log("Failed to initialize SDL library, the reason was: %s", SDL_GetError());
        return -1;
    }

    engineEntry->Window =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (engineEntry->Window == nullptr)
    {
        Debugger_Log("Failed to create SDL window, the reason was: %s", SDL_GetError());
        return -1;
    }

    engineEntry->Renderer = SDL_CreateRenderer(engineEntry->Window, -1, 0);
    if (engineEntry->Renderer == nullptr)
    {
        Debugger_Log("Failed to create SDL renderer, the reason was: %s", SDL_GetError());
        return -1;
    }

    SDL_SetWindowTitle(engineEntry->Window, title);
    Debugger_Log("Successfully initialized the engine.");

    return 0;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void Engine_Tick(EngineEntry* engineEntry, Reloadable* reloadable)
{
    assert(engineEntry != nullptr);
    assert(reloadable != nullptr);

    engineEntry->IsRunning = true;

    SDL_Event event;

    Debugger_Log("Entering engine main loop.");
    while (engineEntry->IsRunning)
    {
        // Event handling.
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    engineEntry->IsRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) engineEntry->IsRunning = false;
                    if (event.key.keysym.sym == SDLK_r) Reloadable_TryLoadingSharedObject(reloadable);
                    if (event.key.keysym.sym == SDLK_SPACE && reloadable->IsValid) reloadable->OnEngineTick();
                    break;
                default:;
            }
        }

        // Render scene.
        SDL_SetRenderDrawColor(engineEntry->Renderer, 0, 0, 0, 255);
        SDL_RenderClear(engineEntry->Renderer);

        SDL_RenderPresent(engineEntry->Renderer);
    }
    Debugger_Log("Finished cycling of engine main loop.");
}

void Engine_Shutdown(const EngineEntry* engineEntry)
{
    assert(engineEntry != nullptr);

    SDL_DestroyRenderer(engineEntry->Renderer);
    SDL_DestroyWindow(engineEntry->Window);
    SDL_Quit();

    Debugger_Log("Cleaned up allocated resources for engine.");
}
