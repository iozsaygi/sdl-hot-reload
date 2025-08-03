# Configure general properties.
cmake_minimum_required(VERSION 3.30)
project(sdl-hot-reload)

# Set the 'CPP' standard.
set(CMAKE_CXX_STANDARD 11)

# Setting output directories to same directory.
# This will help when we are executing reloading operations.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# Remove 'lib' prefix from output.
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")

# Do not allow in-source builds.
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed, please create a 'build' directory to trigger CMake build.")
endif ()

# Download and setup 'SDL' library.
message(STATUS "Starting to download SDL library")
include(FetchContent)
set(SDL_TARGET_REVISION 68bfcb6c5419f51104e74e72ea0f8d405a4615b0)
FetchContent_Declare(SDL GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG ${SDL_TARGET_REVISION} GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SDL)

# Ensure SDL3 is available.
if (NOT SDL3_FOUND AND NOT APPLE)
    message(FATAL_ERROR "Couldn't find SDL3!")
endif ()

# The 'engine' project will be compiled as executable and will watch over working directory to detect changes at runtime.
add_subdirectory(engine)

# The 'game' project will be compiled as shared library and will contain code related to SDL.
add_subdirectory(game)