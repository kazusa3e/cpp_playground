#ifndef FIB_HPP
#define FIB_HPP

#include <cstddef>

auto fib(unsigned n) -> std::size_t;
auto fib_memo(unsigned n) -> std::size_t;
auto fib_calc(unsigned n) -> std::size_t;

#endif
