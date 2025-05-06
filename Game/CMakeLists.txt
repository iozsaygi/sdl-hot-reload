project(Game)

# Register source files for 'Game' project.
add_library(${PROJECT_NAME} SHARED Game.cpp)

# Link the SDL library.
if (WIN32)
    message(STATUS "Binding dependencies for Windows.")

    # Add SDL3 include directories.
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})

    # Link SDL3 library to executable.
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES})
elseif (APPLE)
    message(STATUS "Binding dependencies for macOS.")

    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
endif ()