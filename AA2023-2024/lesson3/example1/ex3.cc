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

static std::mutex mtx;

static
void
write_loop( int imax, int icolor ) {
  char escape{0x1B};
  for ( int i{0}; i < imax; ++i ) {
    mtx.lock();
    std::cout
      << escape << '[' << 31+icolor << 'm' // escape sequence for color
      << "write loop " << i << '\n'
      << escape << '[' << 0 << 'm'; // reset to normal color/background
    mtx.unlock();
    // sleep for
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int
main() {
  // put the write loop in thread
  std::vector<std::thread*> th_write_loops;

  // create and lauch of the threads
  th_write_loops.resize(10);
  for ( int i = 0; i < 10; ++i )
    th_write_loops[i] = new std::thread( write_loop, 10+i, i );


  // wait for thread termination
  for ( auto pth : th_write_loops )
    pth->join();

  std::cout << "Thats all folks!!\n";

  // close all the thread and exit
  //exit(0);
  return 0;
}
