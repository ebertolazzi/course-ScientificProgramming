#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    std::cout << "CMake Simple Example\n";
    std::cout << "2 + 3 = " << calc.add(2, 3) << "\n";
    std::cout << "2 * 3 = " << calc.multiply(2, 3) << "\n";
    return 0;
}
