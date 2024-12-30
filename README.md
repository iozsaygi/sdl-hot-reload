# SDL Hot Reload

Hot reloading is a great engineering project on its own, and this repository aims to provide an environment where we can
research it. Currently, most of the pipeline relies on Win32 APIs, but the core logic that actually handles hot
reloading is layered on top of [SDL](https://www.libsdl.org/) APIs that are pretty much cross-platform.

_Here's a small footage where we are hot reloading a basic rendering call:_

![Render call change](https://github.com/iozsaygi/sdl-hot-reload/blob/main/Showcase/render-call-change.gif)

## Building

### Windows

- Download and install [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/) with the
  `Desktop development with C++` workload
- Ensure that `MSBuild` is added to Windows environment variables
- Download and install [CMake](https://cmake.org/)
- `git clone https://github.com/iozsaygi/sdl-hot-reload`
- `cd` to repository directory
- `mkdir build`
- `cd build`
- `cmake -G "Visual Studio 17 2022" ..`
- `msbuild Root.sln /p:Configuration=Release`

## How does it work?

One of the core aspects of hot reloading is being able to detect changes made to files. Unfortunately, this project
lacks that feature at the moment, but it is on the roadmap.

Currently, the hot reloading works as follows:

1. Launch the `Engine` project
2. Press `Space` to trigger a new build of game code and reload it while the engine is running
    - Keybind can be changed by visiting
      the [Engine.cpp](https://github.com/iozsaygi/sdl-hot-reload/blob/main/Engine/Engine.cpp) file
3. Change the game code and reload it at runtime by repeating step two

## License

[MIT License](https://github.com/iozsaygi/sdl-hot-reload/blob/main/LICENSE)