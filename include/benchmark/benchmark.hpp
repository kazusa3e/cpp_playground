#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#include "../others/noncopyable.hpp"

#if defined(DEBUG) && DEBUG == 1
#warning \
    "Benchmark should NOT run in Debug mode; consider checkout to Release mode."
#endif

// TODO(kazusa): support iteration
// NOLINTBEGIN(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
class benchmark : public noncopyable {
    // NOLINTEND(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
   public:
    benchmark() = delete;
    explicit benchmark(std::string name) : name_(std::move(name)) {
#if defined(DEBUG) && DEBUG == 1
        throw std::runtime_error(
            "Benchmark should NOT run in Debug mode. do nothing.");
#endif
    }
    ~benchmark() {
#if defined(DEBUG) && DEBUG == 1
// do nothing
#else
        const auto end = std::chrono::high_resolution_clock::now();
        const auto dur =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start_)
                .count();
        std::cout << "[BMK] Task " << name_ << " took " << dur << " us" << '\n';
#endif
    }

   private:
    std::string name_;
    std::chrono::high_resolution_clock::time_point start_{
        std::chrono::high_resolution_clock::now()};
};

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define BENCHMARK(name) auto __bm = benchmark{name};
// NOLINTEND(cppcoreguidelines-macro-usage)

#endif
