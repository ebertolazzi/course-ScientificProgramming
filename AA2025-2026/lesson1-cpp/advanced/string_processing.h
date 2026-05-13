#ifndef STRING_PROCESSING_H
#define STRING_PROCESSING_H

#include <iostream>
#include <string>
#include <string_view>
#include <charconv>
#include <algorithm>
#include <array>

void demonstrate_string_processing() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ STRING PROCESSING: Boyer-Moore, to_chars, string_view          │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // Boyer-Moore search
    std::cout << "\n--- Boyer-Moore Search ---\n";
    std::string text = "This is a simple example text for demonstrating "
                       "the Boyer-Moore search algorithm in C++17";
    
    std::string pattern = "Boyer-Moore";
    
    auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    auto [first, last] = searcher(text.begin(), text.end());
    
    if (first != text.end()) {
        std::cout << "Found \"" << pattern << "\" at position: " 
                  << std::distance(text.begin(), first) << "\n";
    }
    
    // to_chars and from_chars
    std::cout << "\n--- to_chars and from_chars ---\n";
    std::array<char, 20> buffer;
    
    if (auto [ptr, ec] = std::to_chars(buffer.data(), 
                                       buffer.data() + buffer.size(), 42);
        ec == std::errc()) {
        std::string_view sv(buffer.data(), ptr - buffer.data());
        std::cout << "to_chars(42): " << sv << "\n";
    }
    
    if (auto [ptr, ec] = std::to_chars(buffer.data(), 
                                       buffer.data() + buffer.size(), 3.14159);
        ec == std::errc()) {
        std::string_view sv(buffer.data(), ptr - buffer.data());
        std::cout << "to_chars(3.14159): " << sv << "\n";
    }
    
    std::string number_str = "12345";
    int value;
    
    if (auto [ptr, ec] = std::from_chars(number_str.data(), 
                                         number_str.data() + number_str.size(), 
                                         value);
        ec == std::errc()) {
        std::cout << "from_chars(\"12345\"): " << value << "\n";
    }
    
    // string_view advanced
    std::cout << "\n--- String View Operations ---\n";
    std::string long_text = "Hello C++17 World! This demonstrates string_view.";
    std::string_view full_view = long_text;
    
    std::string_view hello = full_view.substr(0, 5);
    std::string_view cpp17 = full_view.substr(6, 5);
    
    std::cout << "Original: " << full_view << "\n";
    std::cout << "Parts: " << hello << " " << cpp17 << "\n";
    
    auto pos = full_view.find("string_view");
    if (pos != std::string_view::npos) {
        std::cout << "'string_view' found at position: " << pos << "\n";
    }
}

#endif
