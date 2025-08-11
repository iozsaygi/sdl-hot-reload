#include "engine.h"
#include <cassert>
#include <iostream>

Engine::Engine(const EngineWindow engineWindow, const GameCode& gameCode) {
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

    m_GameCode = gameCode;
}

bool Engine::TriggerGameCodeBuild() {
#ifdef _WIN32
    const std::string command = "msbuild \"" GAME_SOLUTION_FILE_PATH "\" /p:Configuration=Release > NUL 2>&1";
    std::cout << "Executing the game build with following command: " << command.c_str() << std::endl;

    const int result = std::system(command.c_str());
    if (result != 0) std::cout << "Failed to execute the game build with provided command line!" << std::endl;

    return result;
#elif __APPLE__
    const std::string buildDirectory = PROJECT_BUILD_DIRECTORY;
    const std::string command = "cd " + buildDirectory + " && cmake --build . --target game --config Release";

    std::cout << "Executing the game build with following command: " << command.c_str() << std::endl;
    const auto result = std::system(command.c_str());
    if (result != 0) std::cout << "Failed to execute the game build with provided command line!" << std::endl;

    return result == 0;
#else
    return false;
#endif // _WIN32
}

void Engine::FreeGameCodeInstance() {
    assert(m_GameCode.Instance != nullptr);
    m_GameCode.IsValidated = false;
    m_GameCode.OnEngineRenderSceneCallback = nullptr;
    SDL_UnloadObject(m_GameCode.Instance);
}

bool Engine::UpdateGameCodeInstance() {
    // First invalidate the existing instance by freeing it.
    if (m_GameCode.Instance != nullptr) FreeGameCodeInstance();

    // Invalidate the instance to prevent crashes within update loop.
    m_GameCode.IsValidated = false;

    // Trigger new build for the game code.
    if (!TriggerGameCodeBuild()) {
        std::cout << "Failed to build game code" << std::endl;
        return false;
    }

    m_GameCode.Instance = SDL_LoadObject(m_GameCode.Path);
    if (m_GameCode.Instance == nullptr) {
        std::cout << "Failed to load game code, the reason was: " << SDL_GetError() << std::endl;
        return false;
    }

    m_GameCode.OnEngineRenderSceneCallback =
        reinterpret_cast<Game_OnEngineRenderScene>(SDL_LoadFunction(m_GameCode.Instance, "Game_OnEngineRenderScene"));
    if (m_GameCode.OnEngineRenderSceneCallback == nullptr) {
        std::cout << "Failed to load 'OnEngineRenderScene' callback, the reason was: " << SDL_GetError() << std::endl;
        return false;
    }

    m_GameCode.IsValidated = true;

    std::cout << "Successfully updated the game code" << std::endl;

    return true;
}

void Engine::Update() {
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
                        case SDLK_SPACE:
                            UpdateGameCodeInstance();
                            break;
                        default:;
                    }
                    break;
                default:;
            }
        }

        // Render scene.
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_Renderer);

        if (m_GameCode.IsValidated) {
            SDL_FRect rect;
            rect.x = 320;
            rect.y = 200;
            rect.w = 128;
            rect.h = 128;

            m_GameCode.OnEngineRenderSceneCallback(m_Renderer, rect);
        }

        SDL_RenderPresent(m_Renderer);
    }
}

void Engine::Quit() const {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
