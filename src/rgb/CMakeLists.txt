add_library(RGB rgb.cpp)

target_link_libraries(RGB INTERFACE wiringPi pthread)

target_include_directories(RGB INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
