project(game)

# Register source files for 'game' project.
add_library(${PROJECT_NAME} SHARED game.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)