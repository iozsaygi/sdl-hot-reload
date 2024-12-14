#ifndef WATCHER_H
#define WATCHER_H

#include <Windows.h>
#include <atomic>
#include <thread>

struct Win32Observable
{
    const char* Path;
    HANDLE DirectoryHandle;

    std::atomic<bool> IsRunning;
    std::thread WorkerThread;
};

void Watcher_Initialize(Win32Observable* win32Observable);
void Watcher_Observe(const Win32Observable* win32Observable);
void Watcher_Shutdown(Win32Observable* win32Observable);

#endif // WATCHER_H
