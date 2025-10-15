#include <fib/fib.hpp>
#include <format>
#include <iostream>

auto main(int /*argc*/, const char* /*argv*/[]) -> int {
    const auto n = 30;
    std::cout << std::format("fib({}) = {}", n, fib(n)) << '\n';
    return 0;
}
