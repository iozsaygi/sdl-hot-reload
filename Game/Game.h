#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

// TODO: So '__declspec(dllexport)' will be bound to work on Windows, try to find cross-platform compatible way of this
// later on.
extern "C" __declspec(dllexport) void Game_OnEngineRenderScene(SDL_Renderer* renderer, SDL_FRect rect);

#endif // GAME_H
