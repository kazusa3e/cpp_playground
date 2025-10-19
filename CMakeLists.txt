cmake_minimum_required(VERSION 4.0.0)

project(
    CPP_PLAYGROUND
    VERSION 0.1.0
    DESCRIPTION "A C++ project to play around with C++ features"
    LANGUAGES CXX
)

# disable cxx20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_library(mylib INTERFACE)
target_include_directories(mylib INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(mylib INTERFACE cxx_std_20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(mylib INTERFACE OPTIM_LEVEL="O0")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(mylib INTERFACE OPTIM_LEVEL="O3")
endif()

add_subdirectory(src)
add_subdirectory(tests)
