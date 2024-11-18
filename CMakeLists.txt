# Configure general properties.
cmake_minimum_required(VERSION 3.3)
project(Root)

# Set the 'CPP' standard.
set(CMAKE_CXX_STANDARD 11)

# Remove 'lib' prefix from built shared libraries.
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")

# The 'Engine' project will be compiled as executable and will watch over working directory to detect changes at runtime.
add_subdirectory(Engine)

# The 'Player' project will be compiled as shared library and will contain code related to SDL.
add_subdirectory(Player)
