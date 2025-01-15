project(Engine)

# Set the solution directory of 'Game' project as environment variable so we can easily access it during C++ runtime.
# This is totally wrong, it assumes the user is using 'msbuild' and requires porting.
if (WIN32)
    set(GAME_SOLUTION_FILE_PATH "${CMAKE_SOURCE_DIR}/build/Game/Game.sln")
    message(STATUS "[ENGINE] Cached the '.sln' file path of 'Game' project: ${GAME_SOLUTION_FILE_PATH}")
    add_compile_definitions(GAME_SOLUTION_FILE_PATH="${GAME_SOLUTION_FILE_PATH}")
endif ()

# Register source files for 'Engine'.
add_executable(${PROJECT_NAME} Entry.cpp Engine.cpp Watcher.cpp)

# Add SDL include directory.
include_directories(${SDL2_INCLUDE_DIR})

# Link the SDL library.
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
