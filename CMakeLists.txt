cmake_minimum_required(VERSION 3.30)
project(tonkeymype)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
include_directories(${SDL2_INCLUDE_DIRS})

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(tonkeymype src/main.cpp)
target_link_libraries(tonkeymype PRIVATE SDL2)
