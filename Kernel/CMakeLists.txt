project(Kernel)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL/cmake")
find_package(SDL2 REQUIRED)

# Register source files for 'Kernel' project.
add_library(${PROJECT_NAME} SHARED Kernel.cpp)

# Add SDL include directory.
include_directories(${SDL2_INCLUDE_DIR})

# Link the SDL library.
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
