cmake_minimum_required(VERSION 3.10)
project(
    ResolveRoboticsURI
    VERSION 1.0
    DESCRIPTION "Resolve Robotics URI library"
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Locate source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

# Create a library from source files
add_library(resolve_robotics_uri ${SRC_FILES} ${HEADER_FILES})

# Add include directories
target_include_directories(resolve_robotics_uri PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
