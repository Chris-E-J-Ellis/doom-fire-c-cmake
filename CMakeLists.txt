cmake_minimum_required(VERSION 3.26)
project(doom_fire_c_experiment C)

set(CMAKE_C_STANDARD 11)

set(LIBS_DIR ${PROJECT_SOURCE_DIR}/libs)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Could just move this into the sub-folder, messing about
add_subdirectory(src)