#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[])
{
    auto argcReference = argc;
    auto argvReference = argv[1];

    std::cout << "Entry point" << argcReference << argvReference;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}
