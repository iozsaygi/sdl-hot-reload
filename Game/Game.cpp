#include "Game.h"

// Rendering very basic rectangle at the given position.
// Color can be changed to demonstrate hot reloading.
void Game_OnEngineRenderScene(SDL_Renderer* renderer, SDL_FRect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    // SDL_RenderDrawRect(renderer, &rect);
}
