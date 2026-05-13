#ifndef ADVANCED_TECHNIQUES_H
#define ADVANCED_TECHNIQUES_H

#include <iostream>
#include <new>
#include <cstddef>
#include <vector>
#include <tuple>
#include <type_traits>
#include <functional>

// Guaranteed copy elision demonstration
class NonCopyable {
public:
    int value;
    
    NonCopyable(int v) : value(v) {
        std::cout << "Constructor called for " << v << "\n";
    }
    
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};

NonCopyable create_noncopyable() {
    return NonCopyable(42);
}

// Structured bindings with custom types
struct Point3D_Advanced {
    double x, y, z;
};

// Custom class with structured bindings support
class Person {
private:
    std::string name;
    int age;
    
public:
    Person(std::string n, int a) : name(std::move(n)), age(a) {}
    
    // FIXED: return const reference to avoid dropping const qualifier
    template<std::size_t N>
    decltype(auto) get() const {
        if constexpr (N == 0) return (name);
        else if constexpr (N == 1) return (age);
    }
};

// Enable structured bindings for Person
namespace std {
    template<>
    struct tuple_size<Person> : std::integral_constant<std::size_t, 2> {};
    
    template<>
    struct tuple_element<0, Person> { using type = const std::string; };
    
    template<>
    struct tuple_element<1, Person> { using type = const int; };
}

// noexcept in type system
template<typename T>
void check_noexcept() {
    if constexpr (noexcept(T())) {
        std::cout << "T() is noexcept\n";
    } else {
        std::cout << "T() may throw\n";
    }
}

void noexcept_function() noexcept {
    std::cout << "This function is noexcept\n";
}

// FIXED: renamed to avoid conflict with basic/functions_templates.h
constexpr auto factorial_lambda = [](int n) constexpr noexcept {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
};

// Compile-time factorial using the constexpr lambda
template<int N>
struct Factorial {
    static constexpr int value = factorial_lambda(N);
};

void demonstrate_advanced_techniques() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ ADVANCED TECHNIQUES: byte, copy elision, constexpr lambda     │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // std::byte
    std::cout << "\n--- std::byte ---\n";
    std::byte a{0b00001111};
    std::byte c{0b11110000};
    
    auto result_or = a | c;
    auto result_and = a & c;
    
    std::cout << "a: " << std::to_integer<int>(a) << "\n";
    std::cout << "c: " << std::to_integer<int>(c) << "\n";
    std::cout << "a | c: " << std::to_integer<int>(result_or) << "\n";
    std::cout << "a & c: " << std::to_integer<int>(result_and) << "\n";
    
    // Guaranteed copy elision
    std::cout << "\n--- Guaranteed Copy Elision ---\n";
    NonCopyable nc = create_noncopyable();
    std::cout << "Created non-copyable with value: " << nc.value << "\n";
    std::cout << "No copy/move constructor called!\n";
    
    // Structured bindings with custom types
    std::cout << "\n--- Custom Structured Bindings ---\n";
    Point3D_Advanced point{1.0, 2.0, 3.0};
    auto [x, y, z] = point;
    std::cout << "Point: (" << x << ", " << y << ", " << z << ")\n";
    
    const Person person("Alice", 30);
    const auto& [name, age] = person;  // FIXED: using const auto&
    std::cout << "Person: " << name << ", age " << age << "\n";
    
    // noexcept in type system
    std::cout << "\n--- noexcept in Type System ---\n";
    check_noexcept<int>();
    check_noexcept<std::string>();
    
    auto noexc_ptr = noexcept_function;
    std::cout << "noexcept_function is noexcept: " 
              << noexcept(noexc_ptr()) << "\n";
    
    // constexpr lambda
    std::cout << "\n--- constexpr Lambda ---\n";
    constexpr int fact5 = factorial_lambda(5);
    std::cout << "5! = " << fact5 << " (computed at compile time)\n";
    
    constexpr int fact10 = Factorial<10>::value;
    std::cout << "10! = " << fact10 << " (computed at compile time)\n";
    
    // Runtime usage of constexpr lambda
    int n = 6;
    std::cout << "6! = " << factorial_lambda(n) << " (computed at runtime)\n";
    
    // if/switch initializers (C++17)
    std::cout << "\n--- if/switch Initializers ---\n";
    
    if (auto value = 42; value > 40) {
        std::cout << "Value " << value << " is greater than 40\n";
    }
    
    switch (auto code = 2; code) {
        case 1:
            std::cout << "Case 1\n";
            break;
        case 2:
            std::cout << "Case 2\n";
            break;
        default:
            std::cout << "Default\n";
            break;
    }
    
    // Structured binding with pair
    std::cout << "\n--- More Structured Bindings ---\n";
    std::pair<int, std::string> pair{1, "one"};
    auto [num, str] = pair;
    std::cout << num << ": " << str << "\n";
}

#endif
