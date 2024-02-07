/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>

// for timing
#include <chrono>

// for sleep_for
#include <thread>

static
void
write_loop( int imax ) {
  for ( int i{0}; i < imax; ++i ) {
    std::cout << "write loop " << i << '\n';
    // sleep for
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int
main() {
  // put the write loop in thread
  std::thread th_write_loop( write_loop, 10 );
  //  ^            ^            ^         ^
  // type   name of the thread  |         variable number of arguments passed to the thread
  //                       body of the thread


  th_write_loop.join(); // wait for thread termination
  std::cout << "Thats all folks!!\n";

  // close all the thread and exit
  //exit(0);
  return 0;
}
