# SDL Hot Reload

This is an experimental and research repository to learn more about hot reloading game code with the help of
the [SDL](https://www.libsdl.org)
library. The main idea is to compile game code as a shared library and provide an executable program (engine) to manage
game code instances at runtime.

The current workflow relies on macOS APIs, but it should be relatively straightforward to port this workflow to other
operating systems, such as Windows.

![Render call change](https://github.com/iozsaygi/sdl-hot-reload/blob/main/media/render-call-change.gif?raw=true)

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

After running the engine executable, you can press the `Space` key to trigger the update process for the game code
instance. Any changes made to [game.cpp](https://github.com/iozsaygi/sdl-hot-reload/blob/main/game/game.cpp) will be
reflected in the new update of the game code.

In general, here is the current workflow:

1. Press the space key to trigger the update process for the game code instance.
2. Game code will load, and a rectangle will be visible on the screen if the build passes.
3. Change `game.cpp` and press space key again to reflect changes on the engine executable.

## License

[MIT License](https://github.com/iozsaygi/sdl-hot-reload/blob/main/LICENSE)