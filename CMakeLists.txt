# Configure general properties.
cmake_minimum_required(VERSION 3.30)
project(SDLHotReload)

# Set the 'CPP' standard.
set(CMAKE_CXX_STANDARD 11)

# Setting output directories to same directory.
# This will help when we are executing reloading operation.
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

set(PROJECT_BUILD_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
message(STATUS "[ROOT] Cached the root build directory: ${PROJECT_BUILD_DIRECTORY}")
add_compile_definitions(PROJECT_BUILD_DIRECTORY="${PROJECT_BUILD_DIRECTORY}")

# Only downloading and extracting SDL for Windows.
if (WIN32)
    message(STATUS "Executing Windows specific build operations.")

    include(FetchContent)

    set(SDL3_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL")

    # Set the download URL for SDL library.
    set(SDL_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-3.2.8/SDL3-devel-3.2.8-VC.zip")

    # Set the extract directory for downloaded SDL library.
    set(SDL_EXTRACTION_DIRECTORY "${SDL3_DIR}")

    # Download and extract SDL library.
    message(STATUS "Trying to download and extract SDL library.")
    include(FetchContent)
    FetchContent_Declare(SDL URL ${SDL_DOWNLOAD_URL} SOURCE_DIR ${SDL_EXTRACTION_DIRECTORY} DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(SDL)

    find_package(SDL3 REQUIRED PATHS ${SDL3_DIR}/cmake NO_DEFAULT_PATH)
elseif (APPLE)
    message(STATUS "Executing macOS specific build operations.")
    include(FetchContent)
    set(SDL_TARGET_REVISION 877399b2b2cf21e67554ed9046410f268ce1d1b2)
    FetchContent_Declare(SDL GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG ${SDL_TARGET_REVISION} GIT_SHALLOW TRUE)

    # Download and extract SDL image by using specific revision.
    set(SDL_IMAGE_REVISION 11154afb7855293159588b245b446a4ef09e574f)
    FetchContent_Declare(SDL_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG ${SDL_IMAGE_REVISION} GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(SDL SDL_image)
endif ()

# Ensure SDL3 is available.
if (NOT SDL3_FOUND AND NOT APPLE)
    message(FATAL_ERROR "Couldn't find SDL3!")
endif ()

# 'MSVC' related commands.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Performing 'MSVC' specific operations.")

    # Enable all warnings and treat warnings as errors. (Optional)
    # add_compile_options(/W4 /WX)
endif ()

# The 'Engine' project will be compiled as executable and will watch over working directory to detect changes at runtime.
add_subdirectory(Engine)

# The 'Game' project will be compiled as shared library and will contain code related to SDL.
add_subdirectory(Game)
