#include "Watcher.h"
#include <cassert>
#include <string>
#include "Debugger.h"

void Watcher_Initialize(Win32Observable* win32Observable)
{
    assert(win32Observable != nullptr);

    char directoryBuffer[MAX_PATH];

    const DWORD length = GetModuleFileNameA(nullptr, directoryBuffer, MAX_PATH);
    if (length == 0)
    {
        Debugger_Log("Failed to get directory path!");
        return;
    }

    const std::string fullPath(directoryBuffer);
    const size_t lastSlash = fullPath.find_last_of("\\/");
    if (lastSlash != std::string::npos)
    {
        win32Observable->Path = fullPath.substr(0, lastSlash).c_str();
    }

    Debugger_Log("The watcher initialized to observe following directory: %s", win32Observable->Path);

    win32Observable->DirectoryHandle =
        CreateFile(win32Observable->Path, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                   nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

    if (win32Observable->DirectoryHandle == INVALID_HANDLE_VALUE)
    {
        Debugger_Log("Failed to create directory handle, the reason was: %s", GetLastError());
    }

    // Setup thread to watch for directory changes.
    win32Observable->IsRunning = true;
    win32Observable->WorkerThread = std::thread(Watcher_Observe, win32Observable);
    win32Observable->WorkerThread.detach();
}

void Watcher_Observe(const Win32Observable* win32Observable)
{
    // ReSharper disable once CppTooWideScope
    char buffer[1024];
    DWORD bytesReturned;

    while (win32Observable->IsRunning)
    {
        if (ReadDirectoryChangesW(win32Observable->DirectoryHandle, buffer, sizeof(buffer), FALSE,
                                  FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, nullptr, nullptr))
        {
            Debugger_Log("File change detected!");
        }

        // Sleep the thread.
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Watcher_Shutdown(Win32Observable* win32Observable)
{
    win32Observable->IsRunning = false;

    if (win32Observable->WorkerThread.joinable())
    {
        win32Observable->WorkerThread.join();
    }

    CloseHandle(win32Observable->DirectoryHandle);
    win32Observable->DirectoryHandle = INVALID_HANDLE_VALUE;
}
