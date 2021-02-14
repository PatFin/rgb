
add_library(rgb SHARED rgb.cpp)
set_target_properties(rgb PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/rgb.h)

target_link_libraries(rgb INTERFACE wiringPi pthread)
target_include_directories(rgb PUBLIC ${PROJECT_SOURCE_DIR}/include)
