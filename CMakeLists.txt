cmake_minimum_required(VERSION 4.0.0)

project(
    CPP_PLAYGROUND
    VERSION 0.1.0
    DESCRIPTION "A C++ project to play around with C++ features"
    LANGUAGES CXX
)

# disable cxx20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_subdirectory(src)
add_subdirectory(tests)
