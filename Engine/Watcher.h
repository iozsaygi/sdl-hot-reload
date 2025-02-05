#ifndef WATCHER_H
#define WATCHER_H

#include <atomic>
#include <functional>
#include <thread>

struct win32_watcher {
    const char* directory;
    std::thread thread;
    std::function<void()> callback;
    std::atomic<bool> isRunning;
};

int Watcher_TryCreate(const struct win32_watcher* win32Watcher);

#endif // WATCHER_H
