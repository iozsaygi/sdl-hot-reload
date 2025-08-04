#include "game.h"

void Game_OnEngineRenderScene(SDL_Renderer* renderer, const SDL_FRect rect) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
