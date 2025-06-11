#include "Watcher.h"
#include <cstdio>

#ifdef __APPLE__
#include <sys/event.h>
#include <sys/fcntl.h>
#include <unistd.h>
#endif // __APPLE__

#ifdef SDL_HOT_RELOAD_WIN32
#include <windows.h>
#endif // SDL_HOT_RELOAD_WIN32

int Watcher_TryCreate(const struct watcher* watcher, struct game_code* gc, AssetObserver* assetObserver) {
#ifdef SDL_HOT_RELOAD_WIN32
    const auto lpcwstr = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, watcher->directory, -1, lpcwstr, 4096);

    const HANDLE handle =
        CreateFileW(lpcwstr, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

    if (handle == INVALID_HANDLE_VALUE) {
        printf("Failed to create handle for the watcher, the reason was: %lu", GetLastError());
        return -1;
    }

    // ReSharper disable once CppTooWideScope
    BYTE notificationBuffer[1024];

    DWORD returnBuffer;

    auto lastCapturedSystemTime = std::chrono::steady_clock::now();
    // ReSharper disable once CppTooWideScope
    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int changeRegistrationInterval = 5;

    printf("Watcher created and entering the observation loop at %ls\n", lpcwstr);

    while (watcher->isRunning) {
        if (ReadDirectoryChangesW(handle, notificationBuffer, sizeof(notificationBuffer), TRUE,
                                  FILE_NOTIFY_CHANGE_LAST_WRITE, &returnBuffer, nullptr, nullptr)) {

            // Get the system time at the place where notification occurred.
            auto currentSystemTime = std::chrono::steady_clock::now();

            // Calculate the elapsed time in seconds between captured and current system time.
            auto elapsedSeconds =
                std::chrono::duration_cast<std::chrono::seconds>(currentSystemTime - lastCapturedSystemTime);

            // Only register notification if required seconds passed.
            if (elapsedSeconds.count() >= changeRegistrationInterval) {
                printf("File modification detected, executing assigned callback\n");
                lastCapturedSystemTime = currentSystemTime;

                try {
                    watcher->callback(gc);
                } catch (const std::exception& exception) {
                    printf("Exception occurred while executing callback, the reason was: %s\n", exception.what());
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    printf("Finished observation loop for watcher\n");

    CloseHandle(handle);
    delete[] lpcwstr;

    return 0;
#elif __APPLE__
    const int openHandle = open(watcher->directory, O_EVTONLY);
    if (openHandle < 0) {
        printf("Failed to open directory for watcher, the directory was: %s\n", watcher->directory);
        return -1;
    }

    const int eventQueue = kqueue();
    if (eventQueue == -1) {
        printf("Failed to create event queue to read directory changes!");
        close(openHandle);
        return -1;
    }

    struct kevent directoryChangeEvent {};
    EV_SET(&directoryChangeEvent, openHandle, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR, NOTE_WRITE, 0, nullptr);

    printf("Watcher created and entering the observation loop at %s\n", watcher->directory);

    auto lastCapturedSystemTime = std::chrono::steady_clock::now();

    while (watcher->isRunning) {
        struct kevent currentEvent {};
        timespec timeout = {1, 0};

        const int fetchedEvent = kevent(eventQueue, &directoryChangeEvent, 1, &currentEvent, 1, &timeout);
        if (fetchedEvent == -1) {
            printf("Event error occured, terminating watcher!");
            break;
        }

        if (fetchedEvent > 0) {
            if (currentEvent.fflags & NOTE_WRITE) {
                constexpr int changeRegistrationInterval = 5;
                auto currentSystemTime = std::chrono::steady_clock::now();
                auto elapsedSeconds =
                    std::chrono::duration_cast<std::chrono::seconds>(currentSystemTime - lastCapturedSystemTime);

                if (elapsedSeconds.count() >= changeRegistrationInterval) {
                    printf("File modification detected, executing assigned callback\n");
                    lastCapturedSystemTime = currentSystemTime;

                    try {
                        watcher->callback(gc);
                        if (assetObserver->HasChanged()) {
                            printf("Asset observer detect a change on the asset: %s\n", assetObserver->Path);
                            assetObserver->LoadAsset();
                        }
                    } catch (const std::exception& ex) {
                        printf("Exception occurred while executing callback(s): %s\n", ex.what());
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    printf("Finished observation loop for watcher\n");

    // Close file and event handles.
    close(eventQueue);
    close(openHandle);

    return 0;
#else
    return -1;
#endif // SDL_HOT_RELOAD_WIN32
}
