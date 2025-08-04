#include "engine.h"
#include <assert.h>
#include <iostream>

Engine::Engine(const EngineWindow engineWindow) {
    assert(engineWindow.Width > 0);
    assert(engineWindow.Height > 0);
    assert(engineWindow.Title != nullptr && strlen(engineWindow.Title) > 0);

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        std::cout << "Failed to initialize SDL, the reason was: %s\n" << SDL_GetError() << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow(engineWindow.Title, engineWindow.Width, engineWindow.Height, 0);
    if (m_Window == nullptr) {
        std::cout << "Failed to create SDL window, the reason was: %s\n" << SDL_GetError() << std::endl;
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if (m_Renderer == nullptr) {
        std::cout << "Failed to create SDL renderer, the reason was: %s\n" << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetWindowTitle(m_Window, engineWindow.Title);
}

void Engine::Update() const {
    bool isActive = true;
    SDL_Event event;

    // Event handling.
    while (isActive) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isActive = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            isActive = false;
                            break;
                        default:;
                    }
                    break;
                default:;
            }
        }
    }

    // Render scene.
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    // TODO: Render calls goes here.

    SDL_RenderPresent(m_Renderer);
}

void Engine::Quit() const {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
