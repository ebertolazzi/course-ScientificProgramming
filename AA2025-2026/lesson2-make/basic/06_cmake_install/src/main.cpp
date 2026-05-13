#include <iostream>
#include "mylib/mylib.h"

int main() {
    std::cout << mylib::greet("World") << "\n";
    std::cout << "Version: " << mylib::version_major() 
              << "." << mylib::version_minor() << "\n";
    return 0;
}
