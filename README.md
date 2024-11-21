Work in progress, this file will be updated eventually.

Temporarily writing build steps for Windows (MSVC):

```
mkdir build
cd build
CMake -G "Visual Studio 17 2022" ..
msbuild Root.sln /p:Configuration=Release
```
