#include <catch2/catch_test_macros.hpp>
#include <others/noncopyable.hpp>
#include <type_traits>
#include <utility>

// Test class that inherits from noncopyable
class
    TestClass  // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    : public noncopyable {
   public:
    TestClass() = default;
    explicit TestClass(int val) : value(val) {}
    ~TestClass() = default;

    // Move operations are still allowed
    TestClass(TestClass&&) = default;
    auto operator=(TestClass&&) -> TestClass& = default;

    [[nodiscard]] auto get_value() const -> int { return value; }

   private:
    int value = 0;
};

TEST_CASE("noncopyable class prevents copying", "[noncopyable]") {
    SECTION("Copy constructor is deleted") {
        REQUIRE_FALSE(std::is_copy_constructible_v<TestClass>);
    }

    SECTION("Copy assignment operator is deleted") {
        REQUIRE_FALSE(std::is_copy_assignable_v<TestClass>);
    }

    SECTION("Move constructor is available") {
        REQUIRE(std::is_move_constructible_v<TestClass>);
    }

    SECTION("Move assignment operator is available") {
        REQUIRE(std::is_move_assignable_v<TestClass>);
    }
}

TEST_CASE("noncopyable derived class can be constructed and moved",
          "[noncopyable]") {
    SECTION("Default construction works") {
        const TestClass obj;
        REQUIRE(obj.get_value() == 0);
    }

    SECTION("Parameterized construction works") {
        const TestClass obj(
            42);  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

        REQUIRE(obj.get_value() == 42);
    }

    SECTION("Move construction works") {
        TestClass obj1(
            100);  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

        const TestClass obj2(std::move(obj1));
        REQUIRE(obj2.get_value() == 100);
    }

    SECTION("Move assignment works") {
        TestClass obj1(
            200);  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        TestClass obj2;
        obj2 = std::move(obj1);
        REQUIRE(obj2.get_value() == 200);
    }
}

TEST_CASE("noncopyable type traits validation", "[noncopyable]") {
    SECTION("noncopyable itself is not copy constructible") {
        REQUIRE_FALSE(std::is_copy_constructible_v<noncopyable>);
    }

    SECTION("noncopyable itself is not copy assignable") {
        REQUIRE_FALSE(std::is_copy_assignable_v<noncopyable>);
    }
}
