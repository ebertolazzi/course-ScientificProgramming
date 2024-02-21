
#include <thread>
#include <mutex>
#include <vector>

#include <iostream>

// alias for integer
using integer = int;

int
main() {

  std::vector<integer> buffer;

  // allocate the vector and fill with 0
  int N{100};
  buffer.resize(N);
  std::fill( buffer.begin(), buffer.end(), 0 );

  // prepare and run the threads
  auto fun = [&buffer]( int ipos ) -> void { std::this_thread::sleep_for(std::chrono::milliseconds(100)); buffer[ipos] = 1; };
  //             ^
  //             |
  //             +-- capture "buffer" by reference, a modification of buffer inside lambda function
  //                 is "propagated" to main program

  // use a vector of unique pointer to thread to avoid teh necessity
  // to call explicitly the destructor
  std::vector<std::unique_ptr<std::thread>> vthread;
  vthread.reserve(N); // avoid reallocation

  for ( int i{0}; i < buffer.size(); ++i ) {
    //vthread.push_back( std::unique_ptr<std::thread>( new std::thread( fun, i )  ) );
    vthread.emplace_back( new std::thread( fun, i ) );
  }

  // wait for complete
  for ( int i{0}; i < buffer.size(); ++i ) vthread[i]->join();

  // check solution
  bool ok{true};
  for ( int i{0}; ok && i < buffer.size(); ++i ) {
    ok = buffer[i] == 1;
  }
  if ( ok ) std::cout << "test passed!\n";
  else      std::cout << "test failed!\n";

  // call exit to clean kill all the still running threads
  std::exit(0);

  return 0;
}
