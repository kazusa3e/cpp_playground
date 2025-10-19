#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <format>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../others/noncopyable.hpp"

// TODO(kazusa): support iteration
// NOLINTBEGIN(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
class benchmark : public noncopyable {
    // NOLINTEND(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
   public:
    benchmark() = delete;
    explicit benchmark(std::string name) : name_(std::move(name)) {}
    ~benchmark() {
#ifdef OPTIM_LEVEL
        std::cout << "[BMK] The optimization level is: " << OPTIM_LEVEL << '\n';
#endif
        const auto end = std::chrono::high_resolution_clock::now();
        const auto dur =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start_)
                .count();
        std::stringstream ss;
        ss.imbue(std::locale("en_US.UTF-8"));
        ss << std::format("[BMK] Task `\033[7m{}\033[0m` took ", name_);
        ss << std::fixed << "\033[4m" << dur << "\033[0m";
        ss << " us\n";
        std::cout << ss.str();
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
