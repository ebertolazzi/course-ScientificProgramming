#include <iostream>
#include "stringutils.h"

int main() {
    using namespace stringutils;
    
    std::string test = "Hello CMake Library!";
    std::cout << "Original:    " << test << "\n";
    std::cout << "Upper:       " << to_upper(test) << "\n";
    std::cout << "Lower:       " << to_lower(test) << "\n";
    std::cout << "Starts with 'Hello': " << starts_with(test, "Hello") << "\n";
    
    auto parts = split("one,two,three,four", ',');
    std::cout << "Split:       ";
    for (const auto& p : parts) std::cout << p << " ";
    std::cout << "\n";
    
    return 0;
}
