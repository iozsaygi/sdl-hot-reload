#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

#ifdef _WIN32
extern "C" __declspec(dllexport) void Game_OnEngineRenderScene(SDL_Renderer* renderer, SDL_FRect rect);
#elif __APPLE__
extern "C" __attribute__((visibility("default"))) void Game_OnEngineRenderScene(SDL_Renderer* renderer, SDL_FRect rect);
#else
#error "Failed to define exporting API for shared library on current platform!"
#endif // _WIN32

#endif // GAME_H
