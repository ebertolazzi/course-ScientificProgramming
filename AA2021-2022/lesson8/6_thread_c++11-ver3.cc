#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

#define NUM_THREADS 5

int
main (int argc, char *argv[])
{
  thread threads[NUM_THREADS];
  mutex  mutex_var;

  for ( int t = 0 ; t < NUM_THREADS ; ++t ) {
    cerr << "Creating thread N. " << t << "\n";
    auto fun = [&mutex_var]( int numThread ) {
      unsigned sn = (rand()%3)+1 ;
      this_thread::sleep_for(chrono::seconds(sn));
      {
        lock_guard<mutex> lock(mutex_var); // bild lock, and block the mutex
        cerr << "\nThread n. " << numThread << " sleep = " << sn << " Hello World!\n";
      } // destroy lock, release mutex
    };
    threads[t] = std::thread( fun, t );
  }
  // wait all thread terminate
  for ( int t = 0 ; t < NUM_THREADS ; ++t ) {
    {
      lock_guard<std::mutex> lock(mutex_var); // bild lock, and block the mutex
      cerr << "join thread N. " << t << "\n";
    }
    threads[t].join();
  }

  return 0;
}
