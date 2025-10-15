#include <catch2/catch_test_macros.hpp>

#include "your_project_name/fib.hpp"

TEST_CASE("Simple test case", "[fib]") {
    REQUIRE(fib(0) == 0);
    REQUIRE(fib(1) == 1);
    REQUIRE(fib(2) == 1);
    REQUIRE(fib(3) == 2);
    REQUIRE(fib(4) == 3);
    REQUIRE(fib(5) == 5);
    REQUIRE(fib(6) == 8);
    REQUIRE(fib(7) == 13);
    REQUIRE(fib(8) == 21);
    REQUIRE(fib(9) == 34);
    REQUIRE(fib(10) == 55);
}
