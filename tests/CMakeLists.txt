include(FetchContent)

FetchContent_Declare(
    Catch2
    SYSTEM
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_SOURCES "test_*.cc")
add_executable(all_tests ${TEST_SOURCES})
target_link_libraries(all_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(all_tests PRIVATE mylib)

target_link_libraries(all_tests PRIVATE fib)

