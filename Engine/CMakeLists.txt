project(Engine)

# Register source files for 'Engine' project.
add_executable(${PROJECT_NAME} Application.cpp Debugger.cpp Engine.cpp Reloadable.cpp Watcher.cpp)

# Add SDL include directory.
include_directories(${SDL2_INCLUDE_DIR})

# Link the SDL library.
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
