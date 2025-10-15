add_library(fib lib/fib.cc)
target_compile_features(fib PRIVATE cxx_std_20)
target_include_directories(fib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(main bin/main.cc)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE mylib)

target_link_libraries(main PRIVATE fib)
