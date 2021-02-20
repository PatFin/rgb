cmake_minimum_required(VERSION 3.13)

project(rgb VERSION 0.0.1 DESCRIPTION "A small driver for a 32x32 RGB panel")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(apps)


