#include <iostream>


#include "Engine.h"

int main(int argc, char* argv[]) {
    struct render_context rCtx {
        nullptr, // window
        nullptr // renderer
    };

    struct game_code gc {
        false, // isValid
        "Game.dll", // path
        nullptr, // instance
        nullptr // onEngineRenderScene
    };

    if (Engine_Initialize(800, 600, "Engine", &rCtx) != 0) return -1;

    Engine_Update(&rCtx, &gc);
    Engine_Quit(&rCtx);

    return 0;
}
