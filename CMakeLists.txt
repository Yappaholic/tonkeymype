cmake_minimum_required(VERSION 3.30)
project(tonkeymype)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)
set (HEADER_FILES ${CMAKE_SOURCE_DIR}/include)
set (SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/button.cpp)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_ttf_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(tonkeymype ${SOURCES})
target_link_libraries(tonkeymype PRIVATE SDL2 SDL2_ttf)
target_include_directories(tonkeymype PRIVATE ${HEADER_FILES})
