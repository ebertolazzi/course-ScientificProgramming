#ifndef ATTRIBUTES_AND_LITERALS_H
#define ATTRIBUTES_AND_LITERALS_H

#include <iostream>
#include <string>
#include <chrono>
#include <string_view>

[[nodiscard]] int compute_important_value() {
    return 42;
}

[[nodiscard("Memory must be freed")]] void* allocate_memory(size_t size) {
    return malloc(size);
}

void function_with_unused_params([[maybe_unused]] int x, 
                                 [[maybe_unused]] int y) {
    std::cout << "Function with maybe_unused params\n";
}

void demonstrate_fallthrough(int value) {
    switch (value) {
        case 1:
            std::cout << "One ";
            [[fallthrough]];
        case 2:
            std::cout << "or Two ";
            [[fallthrough]];
        case 3:
            std::cout << "or Three";
            break;
        default:
            std::cout << "Other";
            break;
    }
    std::cout << "\n";
}

void demonstrate_attributes_and_literals() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ ATTRIBUTES & LITERALS: nodiscard, fallthrough, hex floats      │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // [[fallthrough]]
    std::cout << "\n--- [[fallthrough]] ---\n";
    demonstrate_fallthrough(1);
    demonstrate_fallthrough(2);
    demonstrate_fallthrough(3);
    
    // [[nodiscard]]
    std::cout << "\n--- [[nodiscard]] ---\n";
    int result = compute_important_value();
    std::cout << "Computed value: " << result << "\n";
    
    void* memory = allocate_memory(100);
    free(memory);
    
    // [[maybe_unused]]
    std::cout << "\n--- [[maybe_unused]] ---\n";
    [[maybe_unused]] int unused_variable = 42;
    function_with_unused_params(1, 2);
    
    // Digit separators
    std::cout << "\n--- Digit Separators ---\n";
    int million = 1'000'000;
    double precise = 3.141'592'653'589'793;
    
    std::cout << "Million: " << million << "\n";
    std::cout << "Precise pi: " << precise << "\n";
    
    // Binary literals
    std::cout << "\n--- Binary Literals ---\n";
    int binary = 0b10101010;
    int binary2 = 0b1111'0000;
    
    std::cout << "Binary 10101010 = " << binary << "\n";
    std::cout << "Binary 1111'0000 = " << binary2 << "\n";
    
    // Hexadecimal float literals (C++17)
    std::cout << "\n--- Hexadecimal Float Literals ---\n";
    double hex_float = 0x1.921fb54442d18p+1;  // Pi approximation
    std::cout << "Hex float pi: " << hex_float << "\n";
    
    // Chrono literals (C++14)
    using namespace std::chrono_literals;
    std::cout << "\n--- Chrono Literals ---\n";
    auto seconds = 30s;
    auto hours = 2h;
    
    std::cout << seconds.count() << " seconds\n";
    std::cout << hours.count() << " hours\n";
    
    // String view literal (C++17)
    using namespace std::string_view_literals;
    auto sv = "Hello string_view literal"sv;
    std::cout << "String view literal: " << sv << " (length: " 
              << sv.length() << ")\n";
}

#endif
