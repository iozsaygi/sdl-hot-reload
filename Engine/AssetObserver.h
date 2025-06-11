#ifndef ASSET_OBSERVER_H
#define ASSET_OBSERVER_H

#include <ctime>

class AssetObserver {
public:
    const char* Path;

    explicit AssetObserver(const char* path);
    bool HasChanged();

private:
    time_t m_LastWriteTime;
};

#endif // ASSET_OBSERVER_H
