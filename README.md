# SDL Hot Reload

This repository aims to provide an environment to research hot reloading C/C++ code by using useful APIs from the
open-source [SDL](https://www.libsdl.org/) library. Currently, I was able to make it work in Windows by
using [MSBuild](https://github.com/dotnet/msbuild). However, it should be easy
to port it to other platforms considering SDL APIs are cross-platform.

## Building

### Windows (MSBuild)

``
// Building both 'Engine' and 'Kernel' targets.
mkdir build
cd build
CMake -G "Visual Studio 17 2022" ..
msbuild Root.sln /p:Configuration=Release
``

## License

[MIT License](https://github.com/iozsaygi/sdl-hot-reload/blob/main/LICENSE)
