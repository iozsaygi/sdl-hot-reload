project(Engine)

# Register source files for 'Engine'.
add_executable(${PROJECT_NAME} Entry.cpp Engine.cpp)

# Add SDL include directory.
include_directories(${SDL2_INCLUDE_DIR})

# Link the SDL library.
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
