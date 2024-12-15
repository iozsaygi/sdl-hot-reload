#include "Engine.h"

int main(int argc, char* argv[]) {
    struct render_context rCtx{};

    if (Engine_Initialize(800, 600, "Engine", &rCtx) != 0) return -1;

    Engine_Update(&rCtx);
    Engine_Quit(&rCtx);

    return 0;
}
