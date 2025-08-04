#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>

// The signature of game code that we will be loading from shared library and call within the engine's render loop.
// This can be expanded with other functions that we would like to hot reload.
typedef void (*Game_OnEngineRenderScene)(SDL_Renderer* renderer, SDL_FRect rect);

struct EngineWindow {
    int Width;
    int Height;
    const char* Title;
};

// Representation of game code that we will be hot reloading.
struct GameCode {
    bool IsValidated;
    const char* Path;

    // So we were using 'void*' here but with SDL3, we have access to 'SDL_SharedObject*' type.
    // Check out: https://wiki.libsdl.org/SDL3/SDL_SharedObject
    SDL_SharedObject* Instance;

    Game_OnEngineRenderScene OnEngineRenderSceneCallback;
};

class Engine {
public:
    explicit Engine(EngineWindow engineWindow, const GameCode& gameCode);

    // Unfortunately this one is pretty much platform dependent.
    bool TriggerGameCodeBuild();

    void Update() const;
    void Quit() const;

private:
    SDL_Renderer* m_Renderer;
    SDL_Window* m_Window;

    GameCode m_GameCode {};
};

#endif // ENGINE_H
