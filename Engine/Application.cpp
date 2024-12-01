#include "Engine.h"

int main(int argc, char* argv[])
{
    // Create entry instance to boot up engine.
    EngineEntry engineEntry{};

    // Instance to keep track of reloadable shared object.
    Reloadable reloadable = {
        false, // IsValid
        "Kernel.dll", // SharedObjectPath
        nullptr // OnEngineTick
    };

    if (Engine_Initialize(800, 600, "Engine", &engineEntry) == 0) Engine_Tick(&engineEntry, &reloadable);

    Engine_Shutdown(&engineEntry);

    return 0;
}
