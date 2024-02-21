
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <condition_variable>

#include <iostream>

// alias for integer
using integer = int;

int
main() {

  std::atomic<integer> running_threads{0};
  std::vector<integer> buffer;

  // condition variable for the barrier part
  std::condition_variable cv;

  // mutex to be associated to condition variable
  std::mutex              cv_m;

  // allocate the vector and fill with 0
  int N{100};
  buffer.resize(N);
  std::fill( buffer.begin(), buffer.end(), 0 );

  // prepare and run the threads
  auto fun = [&buffer,&running_threads,&cv,&cv_m]( int ipos ) -> void {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    buffer[ipos] = 1;
    --running_threads;
    cv.notify_one();

    // wait for this job for the other threads
    {
      std::unique_lock<std::mutex> lock(cv_m);
      std::cerr << "Wait" << ipos << "\n";
      cv.wait(lock, [&running_threads]{ return running_threads == 0; });
      std::cerr << ipos << "...finished waiting";
    }

    // do the second part of the job
    --running_threads;
    buffer[ipos] = 2;
    cv.notify_one();
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

  // wait for complete [BARRIER]
  {
    std::unique_lock<std::mutex> lock(cv_m);
    std::cout << "Waiting... \n";
    cv.wait(lock, [&running_threads,N]{ return running_threads == -N; });
    std::cout << "...finished waiting";
  }

  // check solution
  bool ok{true};
  for ( int i{0}; ok && i < buffer.size(); ++i ) {
    std::cerr << "buffer[" << i << "] = " << buffer[i] << '\n';
    ok = buffer[i] == 2;
  }
  if ( ok ) std::cout << "test passed!\n";
  else      std::cout << "test failed!\n";

  // call exit to clean kill all the still running threads
  std::exit(0);

  return 0;
}
