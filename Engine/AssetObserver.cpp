#include "AssetObserver.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include "SDL3_image/SDL_image.h"

#ifdef __APPLE__
#include <sys/stat.h>
#endif // __APPLE__

AssetObserver::AssetObserver(const char* path, SDL_Renderer* renderer) {
    assert(path != nullptr && strlen(path) > 0);
    Path = path;
    m_Renderer = renderer;
    m_LastWriteTime = 0;
    Texture = nullptr;
}

bool AssetObserver::HasChanged() {
    // TODO: This will require porting to other platforms.
#ifdef __APPLE__
    struct stat assetInformation {};

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

void AssetObserver::LoadAsset() {
    SDL_Texture* previousTexture = Texture;

    Texture = IMG_LoadTexture(m_Renderer, Path);
    if (Texture == nullptr) {
        printf("Failed to load texture from %s\n", Path);
    }
}
