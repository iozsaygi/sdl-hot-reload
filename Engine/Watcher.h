#ifndef WATCHER_H
#define WATCHER_H

#include <windows.h>

// As far as I know, there are no cross-platform APIs provided by SDL that actually listens to directory notifications.
// Most of the solutions rely on writing code specific to the OS we are working on. (Or we can just use third-party
// library just to achieve this.) So a little bit of porting work is required for the watcher.

struct Observable
{
    // Direct path to the directory that we are going to watch over.
    const char* Path;

    HANDLE DirectoryHandle;

    char NotificationBuffer[1024];
    DWORD Result;
};

void Watcher_Initialize(Observable* observable);
void Watcher_WatchForChangesOnDirectory(Observable* observable);
void Watcher_Shutdown(Observable* observable);

#endif // WATCHER_H
