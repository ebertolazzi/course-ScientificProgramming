
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

#include <iostream>

// alias for integer
using integer = int;

int
main() {

  std::atomic<integer> running_threads{0};
  std::vector<integer> buffer;

  // allocate the vector and fill with 0
  int N{100};
  buffer.resize(N);
  std::fill( buffer.begin(), buffer.end(), 0 );

  // prepare and run the threads
  auto fun = [&buffer,&running_threads]( int ipos ) -> void {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    buffer[ipos] = 1;
    --running_threads;
  };
  //             ^
  //             |
  //             +-- capture "buffer" by reference, a modification of buffer inside lambda function
  //                 is "propagated" to main program

  for ( int i{0}; i < buffer.size(); ++i ) {
    // lauch thread detached
    std::thread tmp( fun, i );
    tmp.detach();
    ++running_threads;
  }

  // wait for complete
  while( running_threads > 0 ) std::this_thread::sleep_for(std::chrono::milliseconds(1));

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
