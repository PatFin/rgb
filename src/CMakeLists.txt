add_library(rgb SHARED rgb.cpp)
set_target_properties(rgb PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/rgb.h)

target_link_libraries(rgb INTERFACE wiringPi pthread)
target_include_directories(rgb PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Add configuration for instalation onto system
include(GNUInstallDirs)

install(TARGETS rgb
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(rgb.pc.in rgb.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/src/rgb.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
