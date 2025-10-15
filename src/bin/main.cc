#include <benchmark/benchmark.hpp>
#include <fib/fib.hpp>

auto main(int /*argc*/, const char* /*argv*/[]) -> int {
    {
        BENCHMARK("fib(50)");
        [[maybe_unused]] const auto _ = fib(50);
    }
    {
        BENCHMARK("fib_memo(50)");
        [[maybe_unused]] const auto _ = fib_memo(50);
    }
    {
        BENCHMARK("fib_calc(50)");
        [[maybe_unused]] const auto _ = fib_calc(50);
    }
    return 0;
}
