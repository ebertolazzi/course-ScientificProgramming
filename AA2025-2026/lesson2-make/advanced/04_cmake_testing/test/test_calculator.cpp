#include <iostream>
#include <cassert>
#include "calculator.h"

int main() {
    // Test add
    assert(Calculator::add(2, 3) == 5);
    assert(Calculator::add(-1, 1) == 0);
    
    // Test multiply
    assert(Calculator::multiply(4, 3) == 12);
    assert(Calculator::multiply(0, 5) == 0);
    
    // Test divide
    assert(Calculator::divide(10, 2) == 5.0);
    
    // Test division by zero throws
    bool caught = false;
    try { Calculator::divide(1, 0); }
    catch (const std::runtime_error&) { caught = true; }
    assert(caught);
    
    std::cout << "All tests passed!\n";
    return 0;
}
