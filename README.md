# SDL Hot Reload

Hot reloading is a great engineering project on its own, and this repository aims to provide an environment where we can
research it. Currently, most of the pipeline relies on Win32 APIs, but the core logic that actually handles hot
reloading is layered on top of SDL APIs that are pretty much cross-platform.

_Here's a small footage where we are hot reloading a basic rendering call:_

![Render call change](https://github.com/iozsaygi/sdl-hot-reload/blob/main/Showcase/render-call-change.gif)