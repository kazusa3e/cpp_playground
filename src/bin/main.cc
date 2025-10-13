#include <format>
#include <iostream>
#include <your_project_name/fib.hpp>

auto main(int argc, const char *argv[]) -> int {
    const auto n = 30;
    std::cout << std::format("fib({}) = {}", n, fib(n)) << std::endl;
    return 0;
}
