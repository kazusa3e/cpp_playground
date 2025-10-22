#ifndef UTILS_HPP
#define UTILS_HPP

#include <format>
#include <iterator>
#include <limits>
#include <random>
#include <type_traits>

template <typename Iter>
    requires std::is_arithmetic_v<
        typename std::iterator_traits<Iter>::value_type>
void random_fill(
    Iter begin, Iter end,
    typename std::iterator_traits<Iter>::value_type min = std::numeric_limits<
        typename std::iterator_traits<Iter>::value_type>::min(),
    typename std::iterator_traits<Iter>::value_type max = std::numeric_limits<
        typename std::iterator_traits<Iter>::value_type>::max()) {
    using value_type = typename std::iterator_traits<Iter>::value_type;
    auto rd = std::random_device{};
    auto gen = std::mt19937{rd()};
    if constexpr (std::is_integral_v<value_type>) {
        auto dis = std::uniform_int_distribution{min, max};
        while (begin != end) {
            *begin = dis(gen);
            ++begin;
        }
    } else {
        auto dis = std::uniform_real_distribution{min, max};
        while (begin != end) {
            *begin = dis(gen);
            ++begin;
        }
    }
}

template <typename T>
concept formatable = requires(T value) { std::format("{}", value); };

template <typename T>
    requires formatable<T>
struct std::formatter<std::vector<T>> {  // NOLINT(cert-dcl58-cpp)
    static constexpr char DELIM = ',';
    static constexpr char BEGIN = '[';
    static constexpr char END = ']';
    constexpr auto parse(std::format_parse_context& ctx)
        -> decltype(ctx.begin()) {
        return ctx.begin();
    }
    auto format(const std::vector<T>& vec, std::format_context& ctx) const
        -> decltype(ctx.out()) {
        auto out = ctx.out();
        *out++ = BEGIN;
        for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter) {
            out = std::format_to(out, "{}", *iter);
            if (iter + 1 != vec.cend()) {
                *out++ = DELIM;
                *out++ = ' ';
            }
        }
        *out++ = END;
        return out;
    }
};

#endif
