cmake_minimum_required(VERSION 3.10)
project(praytimeLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source directory relative to this CMakeLists.txt
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Explicitly list the library implementation files
set(LIB_SOURCES ${SRC_DIR}/praytime.cpp)

# Ensure the compiler can find the headers in the src directory
include_directories(${SRC_DIR})

# Enable high-performance optimizations
if(NOT MSVC)
    add_compile_options(-O3 -march=native)
    message(STATUS "Optimization enabled: -O3 -march=native")
endif()

# Create Static Library (libpraytime.a)
add_library(praytime_static STATIC ${LIB_SOURCES})
set_target_properties(praytime_static PROPERTIES OUTPUT_NAME "praytime")

# Create Shared Object (libpraytime.so)
add_library(praytime_shared SHARED ${LIB_SOURCES})
set_target_properties(praytime_shared PROPERTIES OUTPUT_NAME "praytime")

# Create CLI Executable
# We link this to the shared library we just created
add_executable(praytime_cli ${SRC_DIR}/main.cpp)
target_link_libraries(praytime_cli praytime_shared)

# Feedback for the user
message(STATUS "Library Sources: ${LIB_SOURCES}")
message(STATUS "Build target 'praytime_cli' ready for compilation")