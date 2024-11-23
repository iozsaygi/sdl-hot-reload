#include <SDL.h>
#include <iostream>
#include "Debugger.h"

int main(int argc, char* argv[])
{
    const auto argcReference = argc;
    const auto argvReference = argv;

    std::cout << "Entry point: argc=" << argcReference << ", argv[0]=" << (argvReference ? argvReference[0] : "nullptr")
              << std::endl;

    constexpr int x = 5;
    Debugger_Log("Main %d", x);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Quit();

    std::cin.get();
    return 0;
}
