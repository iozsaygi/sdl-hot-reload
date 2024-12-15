#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

struct render_context {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

// Will return '0' on success and '-1' on failure.
int Engine_Initialize(int width, int height, const char* title, struct render_context* rCtx);

void Engine_Update(const struct render_context* rCtx);
void Engine_Quit(const struct render_context* rCtx);

#endif // ENGINE_H
