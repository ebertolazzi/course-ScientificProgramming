#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

#define NUM_THREADS 5

std::mutex mutex_var;

typedef struct { int numThread; } ParameterForThread;

void
PrintHello( ParameterForThread const & pars ) {
  unsigned sn = (rand()%3)+1 ;
  std::this_thread::sleep_for(std::chrono::seconds(sn));
  mutex_var.lock(); // block other thread until unlock
  cerr << "\nThread n. " << pars.numThread << " sleep = " << sn << " Hello World!\n";
  mutex_var.unlock();
}

int
main (int argc, char *argv[])
{
  std::thread        threads[NUM_THREADS] ;
  ParameterForThread pars[NUM_THREADS] ;
 
  for ( int t = 0 ; t < NUM_THREADS ; ++t ) {
    pars[t].numThread = t;
    cout << "Creating thread N. " << t << endl ;
    threads[t] = std::thread( PrintHello, pars[t] );
  }
  // wait all thread terminate
  for ( int t = 0 ; t < NUM_THREADS ; ++t ) {
    cout << "join thread N. " << t << '\n';
    threads[t].join();
  }

  return 0;
}
