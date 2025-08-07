#include "engine.h"

int main(int argc, char* argv[]) {
    constexpr EngineWindow engineWindow = {640, 480, "SDL Hot Reload"};
    constexpr GameCode gameCode = {false, "Game.dylib", nullptr, nullptr};

    Engine engine(engineWindow, gameCode);
    engine.Update();
    engine.Quit();

    return 0;
}
