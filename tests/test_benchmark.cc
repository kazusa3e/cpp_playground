#include <benchmark/benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fib/fib.hpp>

TEST_CASE("benchmark fib(40)", "[benchmark]") {
    try {
        BENCHMARK("fib(40)");
        [[maybe_unused]] const auto _ = fib(40);
    } catch (const std::runtime_error& e) {
        WARN(e.what());
    }

    try {
        BENCHMARK("fib_memo(40)");
        [[maybe_unused]] const auto _ = fib_memo(40);
    } catch (const std::runtime_error& e) {
        WARN(e.what());
    }

    try {
        BENCHMARK("fib_calc(40)");
        [[maybe_unused]] const auto _ = fib_calc(40);
    } catch (const std::runtime_error& e) {
        WARN(e.what());
    }
}
