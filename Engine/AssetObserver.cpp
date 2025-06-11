#include "AssetObserver.h"
#include <assert.h>
#include <cstdio>
#include <string.h>

#ifdef __APPLE__
#include <sys/stat.h>
#endif // __APPLE__

AssetObserver::AssetObserver(const char* path) {
    assert(path != nullptr && strlen(path) > 0);
    Path = path;
    m_LastWriteTime = 0;
}

bool AssetObserver::HasChanged() {
    // TODO: This will require porting to other platforms.
#ifdef __APPLE__
    struct stat assetInformation;

    if (stat(Path, &assetInformation) != 0) {
        printf("Failed to get 'stat' information for the asset at path: %s\n", Path);
        return false;
    }

    // Checking the last write time of file to detect any changes.
    if (assetInformation.st_mtime != m_LastWriteTime) {
        m_LastWriteTime = assetInformation.st_mtime;
        return true;
    }

    return false;
#else
    // Temporarily returning 'false' for other platforms.
    return false;
#endif // __APPLE__
}
