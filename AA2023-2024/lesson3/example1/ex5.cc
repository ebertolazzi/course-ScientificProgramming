/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>

// for timing
#include <chrono>

// for sleep_for and thread
#include <thread>
#include <mutex>

static
void
write_loop( int imax, int icolor ) {
  static std::mutex mtx;
  char escape{0x1B};
  for ( int i{0}; i < imax; ++i ) {
    { // critical section
      std::lock_guard<std::mutex> lock(mtx);
      std::cout
        << escape << '[' << 31+icolor << 'm' // escape sequence for color
        << "write loop " << i << '\n'
        << escape << '[' << 0 << 'm'; // reset to normal color/background
    }
    // sleep for
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int
main() {
  // put the write loop in thread
  std::vector<std::unique_ptr<std::thread>> th_write_loops;

  // create and launch of the threads using unique_ptr for automatic
  // deallocation
  for ( int i = 0; i < 10; ++i )
    th_write_loops.emplace_back( new std::thread( write_loop, 10+i, i ) );

  // wait for thread termination
  for ( auto & ptr : th_write_loops )
    ptr->join();

  std::cout << "Thats all folks!!\n";

  // close all the thread and exit
  //exit(0);
  return 0;
}
