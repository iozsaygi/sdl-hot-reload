#include "Engine.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

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

int Engine_TryUpdateGameCodeInstance(struct game_code* gc) {
    assert(gc != nullptr);

    // Remove the existing game code instance before updating.
    if (gc->instance != nullptr) Engine_FreeGameCodeInstance(gc);

    gc->instance = SDL_LoadObject(gc->path);
    if (gc->instance == nullptr) {
        printf("Failed to load game code, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    // ReSharper disable once CppFunctionalStyleCast
    gc->onEngineRenderScene = Game_OnEngineRenderScene(SDL_LoadFunction(gc->instance, "Game_OnEngineRenderScene"));
    if (gc->onEngineRenderScene == nullptr) {
        printf("Failed to load game render callback from game code, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    gc->isValid = true;
    printf("Successfully updated the game code instance\n");

    return 0;
}

void Engine_FreeGameCodeInstance(struct game_code* gc) {
    assert(gc != nullptr && gc->instance != nullptr);

    SDL_UnloadObject(gc->instance);
    gc->onEngineRenderScene = nullptr;
    gc->instance = nullptr;
    gc->isValid = false;

    printf("Successfully freed the existing game code instance\n");
}

void Engine_Update(const struct render_context* rCtx, struct game_code* gc) {
    assert(rCtx != nullptr);
    assert(gc != nullptr);

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
                        case SDLK_SPACE:
                            Engine_TryUpdateGameCodeInstance(gc);
                            break;
                        case SDLK_KP_ENTER:
                            std::cout << "Solution file path: " << GAME_SOLUTION_FILE_PATH << std::endl;
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

        if (gc->isValid) {
            SDL_Rect rect;
            rect.x = 450;
            rect.y = 350;
            rect.w = 100;
            rect.h = 100;

            gc->onEngineRenderScene(rCtx->renderer, rect);
        }

        SDL_RenderPresent(rCtx->renderer);
    }
}

void Engine_Quit(const struct render_context* rCtx) {
    SDL_DestroyRenderer(rCtx->renderer);
    SDL_DestroyWindow(rCtx->window);
    SDL_Quit();
}
