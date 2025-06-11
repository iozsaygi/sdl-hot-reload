#ifndef ASSET_OBSERVER_H
#define ASSET_OBSERVER_H

#include <ctime>
#include "SDL3/SDL_render.h"

class AssetObserver {
public:
    const char* Path;
    SDL_Texture* Texture;

    explicit AssetObserver(const char* path, SDL_Renderer* renderer);
    bool HasChanged();
    void LoadAsset();

private:
    time_t m_LastWriteTime;
    SDL_Renderer* m_Renderer;
};

#endif // ASSET_OBSERVER_H
