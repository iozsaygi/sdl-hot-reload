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
