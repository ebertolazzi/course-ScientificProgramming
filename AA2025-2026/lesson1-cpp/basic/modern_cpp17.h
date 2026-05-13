#ifndef MODERN_CPP17_H
#define MODERN_CPP17_H

#include <iostream>
#include <string>
#include <optional>
#include <variant>
#include <any>
#include <string_view>
#include <tuple>
#include <vector>
#include <map>

std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

std::variant<int, double, std::string> process_value(int mode) {
    switch (mode) {
        case 1: return 42;
        case 2: return 3.14159;
        case 3: return "Hello World";
        default: return 0;
    }
}

// FIXED: removed unused parameter warning
template<typename T>
auto get_value_type_name([[maybe_unused]] const T& value) {
    if constexpr (std::is_integral_v<T>) {
        return "integral";
    } else if constexpr (std::is_floating_point_v<T>) {
        return "floating point";
    } else if constexpr (std::is_same_v<T, std::string>) {
        return "string";
    } else {
        return "unknown";
    }
}

template<typename... Args>
auto sum_fold(Args... args) {
    return (args + ...);
}

template<typename... Args>
auto logical_and_fold(Args... args) {
    return (args && ...);
}

// FIXED: Point3D moved to advanced_techniques.h only

void demonstrate_modern_cpp17() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ MODERN C++17: optional, variant, any, string_view, folds       │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // std::optional
    std::cout << "\n--- std::optional ---\n";
    auto result1 = divide(10, 2);
    auto result2 = divide(10, 0);
    
    if (result1.has_value()) {
        std::cout << "10 / 2 = " << result1.value() << "\n";
    }
    std::cout << "10 / 0 = " << result2.value_or(-1) << " (no value)\n";
    
    // std::variant
    std::cout << "\n--- std::variant ---\n";
    auto v1 = process_value(1);
    auto v2 = process_value(2);
    auto v3 = process_value(3);
    
    auto visitor = [](const auto& value) {
        std::cout << "Variant holds: " << value << "\n";
    };
    
    std::visit(visitor, v1);
    std::visit(visitor, v2);
    std::visit(visitor, v3);
    std::cout << "v1 as int: " << std::get<int>(v1) << "\n";
    
    // std::any
    std::cout << "\n--- std::any ---\n";
    std::any a = 42;
    std::cout << "any as int: " << std::any_cast<int>(a) << "\n";
    
    a = std::string("C++17");
    std::cout << "any as string: " << std::any_cast<std::string>(a) << "\n";
    
    if (a.type() == typeid(std::string)) {
        std::cout << "Currently holding a string\n";
    }
    
    // std::string_view
    std::cout << "\n--- std::string_view ---\n";
    std::string long_string = "Hello C++17 World!";
    std::string_view sv = long_string;
    
    std::string_view hello = sv.substr(0, 5);
    std::string_view cpp17 = sv.substr(6, 5);
    
    std::cout << "String view substrings: '" << hello 
              << "' and '" << cpp17 << "'\n";
    std::cout << "Original string unchanged: " << long_string << "\n";
    
    // Structured bindings
    std::cout << "\n--- Structured Bindings ---\n";
    
    std::pair<int, double> pair{42, 3.14};
    auto [i, d] = pair;
    std::cout << "Pair: " << i << ", " << d << "\n";
    
    std::tuple<std::string, int, double> tuple{"Alice", 30, 1.65};
    auto [name, age, height] = tuple;
    std::cout << "Tuple: " << name << ", " << age << ", " << height << "\n";
    
    std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}};
    for (const auto& [student, score] : scores) {
        std::cout << student << " scored " << score << "\n";
    }
    
    // if constexpr
    std::cout << "\n--- if constexpr ---\n";
    std::cout << "Type of 42: " << get_value_type_name(42) << "\n";
    std::cout << "Type of 3.14: " << get_value_type_name(3.14) << "\n";
    std::cout << "Type of \"hello\": " 
              << get_value_type_name(std::string("hello")) << "\n";
    
    // Fold expressions
    std::cout << "\n--- Fold Expressions ---\n";
    std::cout << "Sum fold: " << sum_fold(1, 2, 3, 4, 5) << "\n";
    std::cout << "Logical AND fold: " 
              << std::boolalpha 
              << logical_and_fold(true, true, true) << "\n";
    std::cout << "Logical AND fold (with false): " 
              << logical_and_fold(true, false, true) << "\n";
    
    // Template argument deduction (C++17)
    std::cout << "\n--- Class Template Argument Deduction ---\n";
    std::pair p(42, "hello");
    std::vector v = {1, 2, 3, 4, 5};
    std::cout << "Deduced pair: " << p.first << ", " << p.second << "\n";
    
    // constexpr lambda (C++17)
    constexpr auto square_lambda = [](int n) { return n * n; };
    constexpr int result = square_lambda(5);
    std::cout << "constexpr lambda: 5² = " << result << "\n";
}

#endif
