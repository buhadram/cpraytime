cmake_minimum_required(VERSION 3.10)
project(PrayTimeLib VERSION 1.0)

# Set C++ standard to 17, suitable for modern system optimization
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Discover all source files in the src subdirectory
file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(src)

# Create Static Library (libpraytime.a)
add_library(praytime_static STATIC ${SOURCES})
set_target_properties(praytime_static PROPERTIES OUTPUT_NAME "praytime")

# Create Shared Object (libpraytime.so)
add_library(praytime_shared SHARED ${SOURCES})
set_target_properties(praytime_shared PROPERTIES OUTPUT_NAME "praytime")

# Positioning for potential performance flags (e.g., AVX2)
# target_compile_options(praytime_shared PRIVATE -mavx2 -msse4.2)

# Output build information
message(STATUS "Found sources: ${SOURCES}")