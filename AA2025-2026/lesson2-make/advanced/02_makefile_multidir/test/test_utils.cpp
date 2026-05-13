#include <iostream>
#include <cassert>
#include "utils.h"
int main() {
    assert(factorial(0) == 1);
    assert(factorial(5) == 120);
    assert(fibonacci(0) == 0);
    assert(fibonacci(10) == 55);
    std::cout << "All tests passed!\n";
    return 0;
}
