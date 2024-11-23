project(Engine)

# Only downloading and extracting SDL for Windows.
if (WIN32)
    message(STATUS "Executing Windows specific build operations.")

    include(FetchContent)

    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL/cmake")

    # Set the download URL for SDL library.
    set(SDL_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-VC.zip")

    # Set the extract directory for downloaded SDL library.
    set(SDL_EXTRACTION_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/SDL")

    # Download and extract SDL library.
    message(STATUS "Trying to download and extract SDL library.")
    include(FetchContent)
    FetchContent_Declare(SDL URL ${SDL_DOWNLOAD_URL} SOURCE_DIR ${SDL_EXTRACTION_DIRECTORY} DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(SDL)

    find_package(SDL2 REQUIRED)
endif ()

# Register source files for 'Engine' project.
add_executable(${PROJECT_NAME} Debugger.cpp)

# Add SDL include directory.
include_directories(${SDL2_INCLUDE_DIR})

# Link the SDL library.
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
