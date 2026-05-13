#include <iostream>
#include <thread>
int main() {
    std::cout << "Hardware concurrency: " 
              << std::thread::hardware_concurrency() << "\n";
    return 0;
}
