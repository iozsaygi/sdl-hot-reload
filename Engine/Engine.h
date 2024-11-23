#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

struct EngineEntry
{
    bool IsRunning;

    // Native references.
    SDL_Window* Window;
    SDL_Renderer* Renderer;
};

int Engine_Initialize(int width, int height, const char* title, EngineEntry* engineEntry);
void Engine_Tick(EngineEntry* engineEntry);
void Engine_Shutdown(const EngineEntry* engineEntry);

#endif // ENGINE_H
