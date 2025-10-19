#include <benchmark/benchmark.hpp>
#include <fib/fib.hpp>
#include <format>
#include <memory>
#include <numeric>
#include <vector>

#include "others/utils.hpp"

namespace {
auto benchmark_fib() -> void {
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
}

auto benchmark_sum(std::size_t N) -> void {
    auto vdouble = std::vector<double>(N);
    random_fill(vdouble.begin(), vdouble.end(), -100.0, 100.0);
    {
        BENCHMARK("sum use std::accumulate");
        const auto sum = std::accumulate(vdouble.begin(), vdouble.end(), 0.0);
        std::cout << std::format("sum is: {}", sum) << '\n';
    }
    {
        BENCHMARK("sum use std::reduce");
        const auto sum = std::reduce(vdouble.begin(), vdouble.end(), 0.0);
        std::cout << std::format("sum is: {}", sum) << '\n';
    }
    {
        BENCHMARK("sum use loop");
        auto sum = 0.0;
        for (const auto& val : vdouble) {
            sum += val;
        }
        std::cout << std::format("sum is: {}", sum) << '\n';
    }
    {
        BENCHMARK("sum use indirect sum");
        auto sum = std::make_unique<double>(0.0);
        for (const auto& val : vdouble) {
            *sum += val;
        }
        std::cout << std::format("sum is: {}", *sum) << '\n';
    }
}
}  // namespace

auto main(int /*argc*/, const char* /*argv*/[]) -> int {
    // benchmark_fib();
    benchmark_sum(
        4e8);  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    return 0;
}
