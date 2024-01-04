cmake_minimum_required(VERSION 3.5)
project(ResolveRoboticsURI
    VERSION 1.0.0
    DESCRIPTION "Resolve Robotics URI"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_library(ResolveRoboticsURI INTERFACE)
target_include_directories(ResolveRoboticsURI INTERFACE include/)

install(
    TARGETS ResolveRoboticsURI
    EXPORT ResolveRoboticsURIConfig
    DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    EXPORT ResolveRoboticsURIConfig
    DESTINATION cmake
)
