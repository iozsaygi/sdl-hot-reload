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
  `Desktop development with C++` workload
- Ensure that `MSBuild` is added to Windows environment variables
- Download and install [CMake](https://cmake.org/)
- `git clone https://github.com/iozsaygi/sdl-hot-reload`
- Run the `win32-build.bat`

### macOS

#### Through Homebrew

- `git clone https://github.com/iozsaygi/sdl-hot-reload`
- `brew install cmake`
- `chmod +x build.sh`
- `./build.sh`

## How does it work?

1. Launch the `Engine` executable
2. Edit [Game.cpp](https://github.com/iozsaygi/sdl-hot-reload/blob/main/Game/Game.cpp), and it will automatically
   trigger hot reload in the background
3. Press `Space` to manually trigger hot reload (Optional)

## Roadmap

- [x] Being able to automatically update the live game code instance without needing a trigger from keybind
- [ ] Hot reloading assets such as textures
- [x] Supporting other platforms
    - As of May 6th, 2025, the entire system is now ported to macOS.

## License

[MIT License](https://github.com/iozsaygi/sdl-hot-reload/blob/main/LICENSE)