#ifndef WATCHER_H
#define WATCHER_H

#include <atomic>
#include <functional>
#include <thread>
#include "AssetObserver.h"

struct watcher {
    const char* directory;
    std::thread thread;
    std::function<void(struct game_code* gc)> callback;
    std::atomic<bool> isRunning;

    watcher(const char* directoryPass, const std::function<void(struct game_code* gc)>& callbackPass) :
        directory(directoryPass), callback(callbackPass), isRunning(false) {
    }
};

int Watcher_TryCreate(const struct watcher* watcher, struct game_code* gc, AssetObserver* assetObserver);

#endif // WATCHER_H
