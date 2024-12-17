#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

// The signature of game code that we will be loading from shared library and call within the engine's render loop.
// This can be expanded with other functions that we would like to hot reload.
typedef void (*Game_OnEngineRenderScene)(SDL_Renderer* renderer, SDL_Rect rect);

struct render_context {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

struct game_code {
    bool isValid;
    const char* path;
    void* instance;
    Game_OnEngineRenderScene onEngineRenderScene;
};

// Will return '0' on success and '-1' on failure.
int Engine_Initialize(int width, int height, const char* title, struct render_context* rCtx);

int Engine_TriggerGameBuild();

// Just like initialization, will return '0' on success.
int Engine_TryUpdateGameCodeInstance(struct game_code* gc);

void Engine_FreeGameCodeInstance(struct game_code* gc);

void Engine_Update(const struct render_context* rCtx, struct game_code* gc);
void Engine_Quit(const struct render_context* rCtx);

#endif // ENGINE_H
