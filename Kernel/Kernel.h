#ifndef KERNEL_H
#define KERNEL_H

#include <SDL.h>

// TODO: So '__declspec(dllexport)' will be bound to work on Windows, try to find cross-platform compatible way of this
// later on.
extern "C" __declspec(dllexport) void Kernel_OnEngineRenderScene(SDL_Renderer* renderer, SDL_Rect rect);

#endif // KERNEL_H
