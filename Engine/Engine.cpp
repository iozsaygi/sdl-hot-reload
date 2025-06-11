#include "Engine.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "AssetObserver.h"
#include "Watcher.h"

#ifdef __APPLE__
#include <climits>
#include <mach-o/dyld.h>
#include <unistd.h>
#endif // __APPLE__

int Engine_Initialize(const int width, const int height, const char* title, struct render_context* rCtx) {
    assert(width > 0);
    assert(height > 0);
    assert(title != nullptr && strlen(title) > 0);

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        printf("Failed to initialize SDL, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rCtx->window = SDL_CreateWindow(title, width, height, 0);
    if (rCtx->window == nullptr) {
        printf("Failed to create SDL window, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    rCtx->renderer = SDL_CreateRenderer(rCtx->window, nullptr);
    if (rCtx->renderer == nullptr) {
        printf("Failed to create SDL renderer, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetWindowTitle(rCtx->window, title);

    // Set the current working directory to the path of the executable on macOS.
    // TODO: See if we need to handle this for other platforms.
#ifdef __APPLE__
    char executablePath[PATH_MAX];
    uint32_t size = sizeof(executablePath);
    if (_NSGetExecutablePath(executablePath, &size) == 0) {
        char resolvedPath[PATH_MAX];
        if (realpath(executablePath, resolvedPath) != nullptr) {
            const std::string fullPath(resolvedPath);
            const std::string directory = fullPath.substr(0, fullPath.find_last_of('/'));
            chdir(directory.c_str());

            char buffer[PATH_MAX];
            if (getcwd(buffer, sizeof(buffer)) != nullptr) {
                printf("Current working directory is: %s\n", buffer);
            }
        }
    }
#endif // __APPLE__

    return 0;
}

int Engine_TriggerGameBuild() {
#ifdef SDL_HOT_RELOAD_WIN32
    const std::string command = "msbuild \"" GAME_SOLUTION_FILE_PATH "\" /p:Configuration=Release > NUL 2>&1";
    printf("\nExecuting the game build with following command: %s\n", command.c_str());

    const int result = std::system(command.c_str());
    if (result != 0) printf("\nFailed to execute the game build with provided command!\n");

    return result;
#elif __APPLE__
    const std::string buildDirectory = PROJECT_BUILD_DIRECTORY;
    const std::string command = "cd " + buildDirectory + " && cmake --build . --target Game --config Release";

    printf("\nExecuting CMake build command:\n%s\n", command.c_str());
    int result = std::system(command.c_str());
    if (result != 0) printf("\nFailed to execute the game build with provided command!\n");

    return result;
#else
    return -1;
#endif // SDL_HOT_RELOAD_WIN32
}

int Engine_TryUpdateGameCodeInstance(struct game_code* gc) {
    assert(gc != nullptr);

    // We are already setting this to 'false' inside 'Engine_FreeGameCodeInstance(game_code*)' but it leads to crashes.
    // So if we decide the update the game code instance, let's directly set it to invalid before anything else.
    gc->isValid = false;

    // Remove the existing game code instance before updating.
    if (gc->instance != nullptr) Engine_FreeGameCodeInstance(gc);

    if (Engine_TriggerGameBuild() != 0) return -1;

    gc->instance = SDL_LoadObject(gc->path);
    if (gc->instance == nullptr) {
        printf("\nFailed to load game code, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    // ReSharper disable once CppFunctionalStyleCast
    gc->onEngineRenderScene = Game_OnEngineRenderScene(SDL_LoadFunction(gc->instance, "Game_OnEngineRenderScene"));
    if (gc->onEngineRenderScene == nullptr) {
        printf("\nFailed to load game render callback from game code, the reason was: %s\n", SDL_GetError());
        return -1;
    }

    gc->isValid = true;
    printf("\nSuccessfully updated the game code instance\n");

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

    AssetObserver assetObserver("Player.png");

    struct watcher watcher(GAME_SOURCE_CODE_DIRECTORY, Engine_TryUpdateGameCodeInstance);
    watcher.isRunning = true;
    watcher.thread = std::thread(Watcher_TryCreate, &watcher, gc, &assetObserver);

    bool active = true;
    SDL_Event event;

    while (active) {
        // Event handling.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    active = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            active = false;
                            watcher.isRunning = false;
                            break;
                        case SDLK_SPACE:
                            Engine_TryUpdateGameCodeInstance(gc);
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
            SDL_FRect rect;
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
