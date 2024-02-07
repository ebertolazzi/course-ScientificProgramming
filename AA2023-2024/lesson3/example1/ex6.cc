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
#include <deque>

static std::mutex mtx_write, mtx_deque, mtx_data;
//
// data is
// first = the data
// second = from which thread
//
static std::deque<std::pair<int,int>> deque_data;
static std::pair<int,int>             last_read_data;

static
void
write_loop( int th_number, int imax, int icolor ) {
  char escape{0x1B};
  for ( int i{0}; i < imax; ++i ) {
    if ( false ) { // critical section with mutex mtx
      std::lock_guard<std::mutex> lock(mtx_write);
      std::cout
        << escape << '[' << 31+icolor << 'm' // escape sequence for color
        << "write loop " << i << '\n'
        << escape << '[' << 0 << 'm'; // reset to normal color/background
    }

    { // critical section
      std::lock_guard<std::mutex> lock(mtx_deque);
      deque_data.push_back( std::pair<int,int>( i, th_number ) );
    }
    // sleep for
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

static
void
fast_read_loop() {
  while ( true ) {
    // read the stack and puts the readed data in last_read_data
    { // critical section with mutex mtx
      std::lock_guard<std::mutex> lock1(mtx_data);
      std::lock_guard<std::mutex> lock2(mtx_deque);
      if ( !deque_data.empty() ) {
        last_read_data = deque_data.front();
        deque_data.pop_front();
        std::lock_guard<std::mutex> lock(mtx_write);
        std::cout
          << "reding data = "
          << last_read_data.first
          << " from thread = " << last_read_data.second
          << " deque size = " << deque_data.size()
          << '\n';
      }
    }
    // sleep for
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
}

static
void
read_loop( int imax ) {
  char escape{0x1B};
  for ( int i{0}; i < imax; ++i ) {
    { // critical section with mutex mtx
      std::lock_guard<std::mutex> lock(mtx_data);
      std::cout
        << escape << '[' << 31 << 'm' // escape sequence for color
        << "read loop -> data = "
        << last_read_data.first << " thread = "
        << last_read_data.second << '\n'
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
  std::thread th_read_loop( read_loop, 10000 );
  std::thread th_fast_read_loop( fast_read_loop );

  // create and launch of the threads using unique_ptr for automatic
  // deallocation
  for ( int i = 0; i < 10; ++i )
    th_write_loops.emplace_back( new std::thread( write_loop, i, 1000+i, i ) );

  // wait for thread termination
  for ( auto & ptr : th_write_loops ) ptr->join();
  th_read_loop.join();

  std::cout << "Thats all folks!!\n";

  // close all the thread and exit
  //exit(0);
  return 0;
}
