#ifndef WATCHER_H
#define WATCHER_H

#include <atomic>
#include <thread>

struct win32_watcher {
    char* directory;
    std::thread thread;
    std::atomic<bool> isRunning;
};

int Watcher_TryCreate(const struct win32_watcher* win32Watcher);

#endif // WATCHER_H
