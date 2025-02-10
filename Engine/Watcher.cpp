#include "Watcher.h"
#include <cstdio>
#include <windows.h>

int Watcher_TryCreate(const struct win32_watcher* win32Watcher, struct game_code* gc) {
    const auto lpcwstr = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, win32Watcher->directory, -1, lpcwstr, 4096);

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

    while (win32Watcher->isRunning) {
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
                    win32Watcher->callback(gc);
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
}
