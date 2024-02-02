#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

#define NUM_THREADS 5

std::mutex mutex_var;

void
PrintHello( int numThread ) {
  unsigned sn = (rand()%3)+1 ;
  std::this_thread::sleep_for(std::chrono::seconds(sn));
  {
    lock_guard<std::mutex> lock(mutex_var); // bild lock, and block the mutex
    cerr << "\nThread n. " << numThread << " sleep = " << sn << " Hello World!\n";
  } // destroy lock, release mutex
}

int
main (int argc, char *argv[])
{
  std::thread threads[NUM_THREADS];
 
  for ( int t = 0 ; t < NUM_THREADS ; ++t ) {
    cerr << "Creating thread N. " << t << "\n";
    threads[t] = std::thread( PrintHello, t );
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
