cmake_minimum_required(VERSION 3.13)

project(RGB)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_STANDARD_REQUIRED True)

add_subdirectory(rgb)

add_executable(Cascade    cascade.cpp)
add_executable(Cycle      cycle.cpp)
add_executable(Raindrop   raindrop.cpp)
add_executable(Random     random.cpp)

target_link_libraries(Cascade PUBLIC RGB)
target_link_libraries(Cycle PUBLIC RGB)
target_link_libraries(Raindrop PUBLIC RGB)
target_link_libraries(Random PUBLIC RGB)

target_include_directories(Random PUBLIC
                                  "${PROJECT_BINARY_DIR}"
                                  )
