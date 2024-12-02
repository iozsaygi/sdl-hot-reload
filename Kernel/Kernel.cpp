#include "Kernel.h"

// Rendering very basic rectangle at the given position.
// Color can be changed to demonstrate hot reloading.
void Kernel_OnEngineRenderScene(SDL_Renderer* renderer, const SDL_Rect rect)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
