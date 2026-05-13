#ifndef ADVANCED_TEMPLATES_H
#define ADVANCED_TEMPLATES_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <tuple>
#include <utility>

template<template<typename, typename...> class Container, typename T>
class ContainerWrapper {
    Container<T> data;
public:
    void add(const T& value) { data.push_back(value); }
    size_t size() const { return data.size(); }
};

template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, T>
absolute_value(T value) {
    return value < 0 ? -value : value;
}

template<typename T>
typename std::enable_if_t<std::is_floating_point_v<T>, T>
absolute_value(T value) {
    return std::abs(value);
}

template<typename T>
auto process_number(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 2.5;
    } else {
        return value;
    }
}

template<typename... Args>
auto sum_all(Args... args) {
    return (args + ...);
}

template<auto Value>
struct Constant {
    static constexpr auto value = Value;
};

template<typename T>
inline constexpr bool is_numeric_v = std::is_arithmetic_v<T>;

template<typename T>
constexpr T pi = T(3.1415926535897932385);

template<typename, typename = void>
struct has_size_method : std::false_type {};

template<typename T>
struct has_size_method<T, std::void_t<decltype(std::declval<T>().size())>> 
    : std::true_type {};

template<typename T>
inline constexpr bool has_size_method_v = has_size_method<T>::value;

template<typename Callable, typename... Args>
auto call_with_logging(Callable&& func, Args&&... args) {
    std::cout << "Calling function...\n";
    return std::invoke(std::forward<Callable>(func), 
                      std::forward<Args>(args)...);
}

void demonstrate_advanced_templates() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ ADVANCED TEMPLATES: SFINAE, if constexpr, fold expressions     │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    std::cout << "\n--- Template Template Parameters ---\n";
    ContainerWrapper<std::vector, int> vec_wrapper;
    vec_wrapper.add(1);
    vec_wrapper.add(2);
    vec_wrapper.add(3);
    std::cout << "ContainerWrapper size: " << vec_wrapper.size() << "\n";
    
    std::cout << "\n--- SFINAE with enable_if ---\n";
    std::cout << "abs(-42) = " << absolute_value(-42) << " (integral)\n";
    std::cout << "abs(-3.14) = " << absolute_value(-3.14) << " (floating)\n";
    
    std::cout << "\n--- if constexpr ---\n";
    std::cout << "process_number(5) = " << process_number(5) << "\n";
    std::cout << "process_number(3.0) = " << process_number(3.0) << "\n";
    
    std::cout << "\n--- Fold Expressions ---\n";
    std::cout << "sum_all(1,2,3,4,5) = " << sum_all(1, 2, 3, 4, 5) << "\n";
    
    std::cout << "\n--- Auto Template Parameters ---\n";
    Constant<42> int_constant;
    Constant<'A'> char_constant;
    std::cout << "int constant: " << int_constant.value << "\n";
    std::cout << "char constant: " << char_constant.value << "\n";
    
    std::cout << "\n--- Inline Variables ---\n";
    std::cout << "is_numeric_v<int>: " << is_numeric_v<int> << "\n";
    std::cout << "is_numeric_v<std::string>: " << is_numeric_v<std::string> << "\n";
    
    std::cout << "\n--- Variable Templates ---\n";
    std::cout << "pi<double>: " << pi<double> << "\n";
    std::cout << "pi<float>: " << pi<float> << "\n";
    
    std::cout << "\n--- Detection Idiom ---\n";
    std::cout << "vector has size(): " << has_size_method_v<std::vector<int>> << "\n";
    std::cout << "int has size(): " << has_size_method_v<int> << "\n";
    
    std::cout << "\n--- std::invoke ---\n";
    auto add = [](int a, int b) { return a + b; };
    std::cout << "Invoke result: " << call_with_logging(add, 3, 4) << "\n";
    
    auto tuple = std::make_tuple(10, 20);
    std::cout << "Apply result: " << std::apply(add, tuple) << "\n";
}

#endif
