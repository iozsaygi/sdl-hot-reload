project(Game)

# Register source files for 'Game' project.
add_library(${PROJECT_NAME} SHARED Game.cpp)

# Add SDL include directory.
include_directories(${SDL3_INCLUDE_DIR})

# Link the SDL library.
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES})
