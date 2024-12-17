This file will be updated eventually.

## Notes
- Had to add `msbuild` to environment variables in Windows.

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
