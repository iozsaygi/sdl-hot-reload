#ifndef KERNEL_H
#define KERNEL_H

// TODO: So '__declspec(dllexport)' will be bound to work on Windows, try to find cross-platform compatible way of this
// later on.
extern "C" __declspec(dllexport) void Kernel_OnEngineRenderScene();

#endif // KERNEL_H
