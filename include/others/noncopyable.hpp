#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

class noncopyable {
   public:
    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable(const noncopyable&) = delete;
    auto operator=(const noncopyable&) -> noncopyable& = delete;

    noncopyable(noncopyable&&) = default;
    auto operator=(noncopyable&&) -> noncopyable& = default;
};

#endif
