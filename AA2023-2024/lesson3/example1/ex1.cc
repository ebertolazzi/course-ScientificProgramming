/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>

// for timing
#include <chrono>

// for sleep_for
#include <thread>

/*

for c++14 you can use literals

static
void
write_loop() {
  using namespace std::chrono_literals;
  for ( int i{0};; ++i ) {
    std::cout << "write loop " << i << '\n';
    // sleep for
    std::this_thread::sleep_for(500ms);
  }
}

*/


static
void
write_loop() {
  for ( int i{0};; ++i ) {
    std::cout << "write loop " << i << '\n';
    // sleep for
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int
main() {
  write_loop();
  return 0;
}
