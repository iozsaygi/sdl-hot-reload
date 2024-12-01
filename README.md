# SDL Hot Reload

This repository aims to provide an environment to research hot reloading C/C++ code by using useful APIs from the
open-source [SDL](https://www.libsdl.org/) library. Currently, I was able to make it work in Windows by
using [MSBuild](https://github.com/dotnet/msbuild). However, it should be easy
to port it to other platforms considering SDL APIs are cross-platform.

## The Idea

Hot reloading approaches game development in a different way. In a regular game development environment, we are usually
compiling our game code as an executable, but with hot reloading we are basically leaving that approach and starting to
compile our game code as shared objects. However, we are still building an executable that has the responsibility to
load and unload our game code.

In this repository there are two different CMake targets; the first one is the `Engine`, and it is responsible for
loading and unloading the shared object from memory by reading keyboard inputs from the user. The engine is basically
powered by cross-platform APIs that SDL provides.

The other target is the `Kernel` project; at least for this repository, it is just a basic source file that prints out a
string to the console and does nothing fancy at all. Kernel gets compiled as a shared object.

## Building

### Windows (MSBuild)

```
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
msbuild Root.sln /p:Configuration=Release
```

## License

[MIT License](https://github.com/iozsaygi/sdl-hot-reload/blob/main/LICENSE)
