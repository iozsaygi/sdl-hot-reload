REM Try to create specific build folder
mkdir build

REM Switch to build folder
cd build

REM Execute the CMake generator
cmake -G "Visual Studio 17 2022" ..

REM Build the root solution
msbuild Root.sln /p:Configuration=Release

echo Executed Win32 build process
pause