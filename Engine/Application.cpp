#include "Engine.h"

int main(int argc, char* argv[])
{
    EngineEntry engineEntry{};

    if (Engine_Initialize(800, 600, "Engine", &engineEntry) == 0)
    {
        SDL_Delay(3000);
    }

    Engine_Shutdown(&engineEntry);

    return 0;
}
