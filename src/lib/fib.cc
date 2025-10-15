#include <cstddef>
#include <fib/fib.hpp>

auto fib(unsigned n) -> std::size_t {  // NOLINT(misc-no-recursion)
    if (n == 0 || n == 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}
