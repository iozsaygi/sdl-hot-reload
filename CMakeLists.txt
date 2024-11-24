# Configure general properties.
cmake_minimum_required(VERSION 3.3)
project(Root)

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

# 'MSVC' related commands.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Performing 'MSVC' specific operations.")

    # Enable all warnings and treat warnings as errors. (Optional)
    # add_compile_options(/W4 /WX)
endif ()

# The 'Engine' project will be compiled as executable and will watch over working directory to detect changes at runtime.
add_subdirectory(Engine)

# The 'Kernel' project will be compiled as shared library and will contain code related to SDL.
add_subdirectory(Kernel)
