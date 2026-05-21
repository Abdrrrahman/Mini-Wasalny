cmake_minimum_required(VERSION 3.10)

project(RaylibProject)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(raylib)

add_executable(graphs
    src/graphs.cpp
)

target_link_libraries(graphs raylib)