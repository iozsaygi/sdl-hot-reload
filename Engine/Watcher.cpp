#include "Watcher.h"
#include "Debugger.h"

#include <cassert>

void Watcher_Initialize(Observable* observable)
{
    assert(observable != nullptr);

    // TODO: This is win32 only, try to support UNIX.

    observable->DirectoryHandle =
        CreateFile(observable->Path, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                   nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

    if (observable->DirectoryHandle == INVALID_HANDLE_VALUE)
    {
        Debugger_Log("Failed to create directory handle for watcher, the reason was: %s", GetLastError());
        return;
    }
}

void Watcher_WatchForChangesOnDirectory(Observable* observable)
{
    assert(observable != nullptr);

    if (ReadDirectoryChangesW(
            observable->DirectoryHandle, observable->NotificationBuffer, sizeof(observable->NotificationBuffer), TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES |
                FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE,
            &observable->Result, nullptr, nullptr))
    {
        Debugger_Log("Change detected on watched directory!");
    }
}

void Watcher_Shutdown(Observable* observable)
{
    CloseHandle(observable->DirectoryHandle);
    observable->DirectoryHandle = INVALID_HANDLE_VALUE;
}
