#include "Engine.h"
#include <cassert>
#include <cstdio>
#include <cstring>

int Engine_Initialize(const int width, const int height, const char* title, struct render_context* rCtx) {
    assert(width > 0);
    assert(height > 0);
    assert(title != nullptr && strlen(title) > 0);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialize SDL, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rCtx->window =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (rCtx->window == nullptr) {
        printf("Failed to create SDL window, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rCtx->renderer = SDL_CreateRenderer(rCtx->window, -1, 0);
    if (rCtx->renderer == nullptr) {
        printf("Failed to create SDL renderer, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetWindowTitle(rCtx->window, title);

    return 0;
}

void Engine_Update(const struct render_context* rCtx) {
    assert(rCtx != nullptr);

    bool active = true;
    SDL_Event event;

    while (active) {
        // Event handling.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    active = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            active = false;
                            break;
                        default:;
                    }
                    break;
                default:;
            }
        }

        // Render scene.
        SDL_SetRenderDrawColor(rCtx->renderer, 0, 0, 0, 255);
        SDL_RenderClear(rCtx->renderer);

        SDL_RenderPresent(rCtx->renderer);
    }
}

void Engine_Quit(const struct render_context* rCtx) {
    SDL_DestroyRenderer(rCtx->renderer);
    SDL_DestroyWindow(rCtx->window);
    SDL_Quit();
}
