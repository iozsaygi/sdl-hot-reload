# SDL Hot Reload

Hot reloading is a great engineering project on its own, and this repository aims to provide an environment where we can
research it. Currently, most of the pipeline relies on Win32 APIs, but the core logic that actually handles hot
reloading is layered on top of [SDL](https://www.libsdl.org/) APIs that are pretty much cross-platform.

_Here's a small footage where we are hot reloading a basic rendering call:_

![Render call change](https://github.com/iozsaygi/sdl-hot-reload/blob/main/Showcase/render-call-change.gif)

The project consists of two different CMake targets: one is `Engine` (built as an executable), and the other is `Game` (
built as a shared library). Engine is the actual system that manages the instance of game code at runtime, and game is
just a basic render call that draws a rectangle on the screen. Memory and objects are allocated within the engine's
scope in order to keep the game state persistent between hot reload calls.

I wrote a [blog post](https://iozsaygi.github.io/2025/01/06/hot-reloading-ccpp-code-with-sdl.html) about this recently;
check it if you want to get a bit more detail.

## Building

### Windows

- Download and install [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/) with the
  `Desktop development with C++` workload.
- Ensure that `MSBuild` is added to Windows environment variables.
- Download and install [CMake](https://cmake.org/).
- Run `git clone https://github.com/iozsaygi/sdl-hot-reload` command.
- Run the `win32-build.bat` build script.

## How does it work?

One of the core aspects of hot reloading is being able to detect changes made to files. Unfortunately, this project
lacks that feature at the moment, but it is on the roadmap.

_Currently, the hot reloading works as follows:_

1. Launch the `Engine` executable.
2. Press `Space` to trigger a new build of game code and reload it while the engine is running.
    - Keybind can be changed by visiting
      the [Engine.cpp](https://github.com/iozsaygi/sdl-hot-reload/blob/main/Engine/Engine.cpp) file.
3. Change the game code and reload it at runtime by repeating step two.

## Roadmap

- [ ] Being able to automatically update the live game code instance without needing a trigger from keybind.
- [ ] Hot reloading assets such as textures.
- [ ] Supporting other platforms.

## License

[MIT License](https://github.com/iozsaygi/sdl-hot-reload/blob/main/LICENSE)