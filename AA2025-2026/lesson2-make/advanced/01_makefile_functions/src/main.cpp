#include <iostream>
int main() {
    std::cout << "Makefile Advanced Functions Demo\n";
#ifdef DEBUG
    std::cout << "Debug mode enabled\n";
#endif
#ifdef USE_FEATURE_X
    std::cout << "Feature X enabled\n";
#endif
#ifdef LINUX
    std::cout << "Running on Linux\n";
#endif
#ifdef MACOS
    std::cout << "Running on macOS\n";
#endif
    return 0;
}
