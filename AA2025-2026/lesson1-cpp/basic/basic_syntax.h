#ifndef BASIC_SYNTAX_H
#define BASIC_SYNTAX_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

enum class Color { Red, Green, Blue };

void demonstrate_basic_syntax() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ BASIC SYNTAX: auto, constexpr, range-for, lambdas, if-init    │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // 1. Type deduction with auto
    auto integer = 42;
    auto floating = 3.14;
    auto character = 'A';
    auto text = std::string("Hello");
    
    std::cout << "Auto-deduced types: int=" << integer 
              << ", double=" << floating 
              << ", char=" << character 
              << ", string=" << text << "\n";
    
    // 2. Const and constexpr
    const double PI = 3.14159;
    constexpr int COMPILE_TIME_CONSTANT = 100;
    std::cout << "Const PI: " << PI << ", constexpr: " << COMPILE_TIME_CONSTANT << "\n";
    
    // 3. Uniform initialization
    int array[]{1, 2, 3, 4, 5};
    std::vector<int> vec{10, 20, 30, 40};
    std::cout << "Array first element: " << array[0] << ", size: " << sizeof(array)/sizeof(array[0]) << "\n";
    
    // 4. Range-based for loop
    std::cout << "Range-based for: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "\n";
    
    // 5. Lambda expressions
    auto square = [](int x) -> int { return x * x; };
    std::cout << "Lambda square(5) = " << square(5) << "\n";
    
    // 6. If with initializer (C++17)
    if (auto it = std::find(vec.begin(), vec.end(), 20); it != vec.end()) {
        std::cout << "Found 20 at position: " 
                  << std::distance(vec.begin(), it) << "\n";
    }
    
    // 7. Structured bindings (C++17)
    auto [r, g, b] = std::make_tuple(Color::Red, Color::Green, Color::Blue);
    std::cout << "Structured bindings with enum class values: " 
              << static_cast<int>(r) << ", " 
              << static_cast<int>(g) << ", " 
              << static_cast<int>(b) << "\n";
    
    // 8. Enum class type safety
    Color paint = Color::Red;
    paint = Color::Blue;
    std::cout << "Enum class paint set to Blue (value: " << static_cast<int>(paint) << ")\n";
}

#endif
