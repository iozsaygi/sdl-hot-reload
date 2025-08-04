#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>

struct EngineWindow {
    int Width;
    int Height;
    const char* Title;
};

class Engine {
public:
    explicit Engine(EngineWindow engineWindow);

    void Update() const;
    void Quit() const;

private:
    SDL_Renderer* m_Renderer;
    SDL_Window* m_Window;
};

#endif // ENGINE_H
