#ifndef WATCHER_H
#define WATCHER_H

#include <atomic>
#include <functional>
#include <thread>

struct win32_watcher {
    const char* directory;
    std::thread thread;
    std::function<void(struct game_code* gc)> callback;
    std::atomic<bool> isRunning;

    win32_watcher(const char* directoryPass, const std::function<void(struct game_code* gc)>& callbackPass) :
        directory(directoryPass), callback(callbackPass), isRunning(false) {
    }
};

int Watcher_TryCreate(const struct win32_watcher* win32Watcher, struct game_code* gc);

#endif // WATCHER_H
