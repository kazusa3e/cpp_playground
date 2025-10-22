#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include <array>
#include <chrono>
#include <cstdint>
#include <format>
#include <iostream>
#include <mutex>
#include <ostream>
#include <others/noncopyable.hpp>
#include <source_location>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>

enum class log_level : std::uint8_t {
    DEBUG,
    // TODO(kazusa): PREF?
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

static constexpr std::array<std::string_view, 5> level_names = {
    "DBG", "INF", "WRN", "ERR", "CRT"};

template <>
struct std::formatter<std::thread::id> {
    static constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }
    static auto format(const std::thread::id &tid, std::format_context &ctx) {
        std::ostringstream oss;
        oss << tid;
        return std::format_to(ctx.out(), "{}", oss.str());
    }
};

class logger : noncopyable {
   public:
    logger() = default;
    void set_level(log_level level) { level_ = level; }

    template <typename... Args>
    void log(log_level level, const std::source_location &loc,
             std::string_view fmt,
             Args &&...args) {  // NOLINT(cppcoreguidelines-missing-std-forward)
        if (level < level_) {
            return;
        }

        const auto now = std::chrono::system_clock::now();
        const auto tid = std::this_thread::get_id();

        auto msg = std::string{};
        if constexpr (sizeof...(args) > 0) {
            msg = std::vformat(fmt, std::make_format_args(args...));
        } else {
            msg = fmt;
        }

        // NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
        const auto line = std::format("[{}] [{}] [{}] [{}:{}] {}", now,
                                      level_names[static_cast<uint8_t>(level)],
                                      tid, loc.file_name(), loc.line(), msg);
        // NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
        {
            const auto lck = std::unique_lock{mtx_};
            os_ << line << "\n";
        }
    }

   private:
    log_level level_{log_level::DEBUG};
    std::mutex mtx_;
    std::ostream &os_{std::cout};
};

#define dbg(fmt, ...)                                                    \
    logger().log(log_level::DEBUG, std::source_location::current(), fmt, \
                 ##__VA_ARGS__)
#define inf(fmt, ...)                                                   \
    logger().log(log_level::INFO, std::source_location::current(), fmt, \
                 ##__VA_ARGS__)
#define wrn(fmt, ...)                                                      \
    logger().log(log_level::WARNING, std::source_location::current(), fmt, \
                 ##__VA_ARGS__)
#define err(fmt, ...)                                                    \
    logger().log(log_level::ERROR, std::source_location::current(), fmt, \
                 ##__VA_ARGS__)
#define crt(fmt, ...)                                                       \
    logger().log(log_level::CRITICAL, std::source_location::current(), fmt, \
                 ##__VA_ARGS__)

#endif
