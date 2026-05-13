#include <iostream>
int main() {
    std::cout << "Generator Expressions Demo\n";
#ifdef MY_DEFINE
    std::cout << "MY_DEFINE is set\n";
#endif
#ifdef NDEBUG
    std::cout << "Release mode\n";
#else
    std::cout << "Debug mode\n";
#endif
#ifdef OS_LINUX
    std::cout << "Linux platform\n";
#endif
#ifdef OS_MACOS
    std::cout << "macOS platform\n";
#endif
    return 0;
}
