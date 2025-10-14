cmake_minimum_required(VERSION 4.0.0)

project(
    YOUR_PROJECT_NAME
    VERSION 0.1.0
    DESCRIPTION "YOUR_PROJECT_DESCRIPTION"
    LANGUAGES CXX
)

# disable cxx20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_subdirectory(src)
add_subdirectory(tests)
