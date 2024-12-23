# SDL Hot Reload

This is an experimental project that aims to research hot reloading C/C++ code by using useful APIs within the SDL
library. Supporting cross-platform is currently an issue considering some parts of the code (including the build
pipeline) rely on Win32-based APIs. However, the core logic that is responsible for managing hot reloading is dependent
on cross-platform SDL APIs.

## Idea

Hot reloading approaches to game development in a different context. Enables us to write our gameplay code as shared
libraries and build a pipeline to refresh the live code instance whenever a change is detected. This is a bit different
than a scenario where we are directly building our gameplay code as an executable. If we take the idea one step further,
we can even implement this to reload game assets (such as textures, audio files, etc.) at runtime.

## Project Structure

The current repository is divided into two different CMake targets called `Engine` and `Game`.

The engine is the actual executable that is responsible for reloading the game code at runtime, and it also stores the
required memory for the game code so the game state won't change between reloads.

Game is the actual gameplay code that we are compiling and building as a shared library. Note that it is really a simple
one that just creates a render call for a rectangle.