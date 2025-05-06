#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

// TODO: So '__declspec(dllexport)' will be bound to work on Windows, try to find cross-platform compatible way of this
// later on.
#ifdef SDL_HOT_RELOAD_WIN32
extern "C" __declspec(dllexport) void Game_OnEngineRenderScene(SDL_Renderer* renderer, SDL_FRect rect);
#elif __APPLE__
__attribute__((visibility("default"))) void Game_OnEngineRenderScene(SDL_Renderer* renderer, SDL_FRect rect);
#else
#error "Failed to define exporting API for shared library on current platform!"
#endif // SDL_HOT_RELOAD_WIN32

#endif // GAME_H
