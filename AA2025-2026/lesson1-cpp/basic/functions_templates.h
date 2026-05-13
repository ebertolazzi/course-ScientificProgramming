#ifndef FUNCTIONS_TEMPLATES_H
#define FUNCTIONS_TEMPLATES_H

#include <iostream>
#include <string>
#include <type_traits>

void print_value(int value) {
    std::cout << "Integer: " << value << "\n";
}

void print_value(double value) {
    std::cout << "Double: " << value << "\n";
}

void greet(const std::string& name = "Guest", int age = 0) {
    std::cout << "Hello " << name;
    if (age > 0) std::cout << ", age " << age;
    std::cout << "\n";
}

template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<>
std::string maximum<std::string>(std::string a, std::string b) {
    return (a.length() > b.length()) ? a : b;
}

template<typename T>
T sum(T value) {
    return value;
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

void demonstrate_functions() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ FUNCTIONS & TEMPLATES: overloading, templates, constexpr       │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    print_value(42);
    print_value(3.14);
    
    greet();
    greet("Alice", 25);
    
    std::cout << "Max(10, 20) = " << maximum(10, 20) << "\n";
    std::cout << "Max(3.14, 2.72) = " << maximum(3.14, 2.72) << "\n";
    std::cout << "Max(short, longer) = " 
              << maximum(std::string("short"), std::string("longer")) << "\n";
    
    std::cout << "Sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    
    constexpr int fact5 = factorial(5);
    std::cout << "Factorial(5) = " << fact5 << " (computed at compile time)\n";
    
    std::cout << "Multiply(3, 2.5) = " << multiply(3, 2.5) << "\n";
    
    static_assert(factorial(5) == 120, "Factorial calculation is wrong!");
    std::cout << "static_assert passed for factorial\n";
}

#endif
