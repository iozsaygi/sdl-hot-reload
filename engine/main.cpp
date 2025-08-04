#include "engine.h"

int main(int argc, char* argv[]) {
    constexpr EngineWindow engineWindow = {640, 480, "SDL Hot Reload"};

    const Engine engine(engineWindow);
    engine.Update();
    engine.Quit();

    return 0;
}
