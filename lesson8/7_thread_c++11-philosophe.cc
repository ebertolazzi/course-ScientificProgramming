/*
 NON WORKING version of Philosophe problem

 level 1: make the code woking
 level 2: make all the philosophe eating on average
 level 3: make the average of eating for each philosophe nearly the same
 levet 4: optimize the resource usage.

 use lambda functions and auto to simplify the code.

*/

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

typedef enum { THINKING, EATING, SLEEPING } PHILOSOPHE_STATE;
typedef enum { FREE, IN_USE } FORK_STATE;

static int const N_PHILOSOPHE = 5;
static vector<PHILOSOPHE_STATE> philosophe_state(N_PHILOSOPHE);
static vector<FORK_STATE>       fork_state(N_PHILOSOPHE);

mutex mutex_var;

static ofstream logfile;

void
get_the_right_fork( int n ) { // for Philosophe n
  lock_guard<mutex> lock(mutex_var);
  int f_right = (n+1) % N_PHILOSOPHE;
  if ( fork_state[f_right] == IN_USE ) {
    logfile << "Philosophe N." << n << " wait for the right fork\n" << flush;
    while ( fork_state[f_right] == IN_USE ); // wait for the fork to be fred
  }
  fork_state[f_right] = IN_USE ; // get the right fork
  logfile << "Philosophe N." << n << " acquired the right fork\n" << flush;
}

void
get_the_left_fork( int n ) { // for Philosophe n
  lock_guard<mutex> lock(mutex_var);
  int f_left = (n-1) % N_PHILOSOPHE;
  if ( fork_state[f_left] == IN_USE ) {
    logfile << "Philosophe N." << n << " wait for the left fork\n" << flush;
    while ( fork_state[f_left] == IN_USE ); // wait for the fork to be fred
  }
  fork_state[f_left] = IN_USE ; // get the left fork
  logfile << "Philosophe N." << n << " acquired the left fork\n" << flush;
}

void
release_the_right_fork( int n ) {
  lock_guard<mutex> lock(mutex_var);
  int f_right = (n+1) % N_PHILOSOPHE ;
  fork_state[f_right] = FREE ;
  logfile << "Filosofo N." << n << " fred the right fork\n" << flush;
}

void
release_the_left_fork( int n ) {
  lock_guard<mutex> lock(mutex_var);
  int f_left = (n-1) % N_PHILOSOPHE ;
  fork_state[f_left] = FREE ;
  logfile << "Filosofo N." << n << " fred the left fork\n" << flush;
}

// running thread for each Philosophe
void
Philosophe( int n ) {

  while ( true ) { // infnite loop
    philosophe_state[n] = THINKING;
    logfile << "The Philosophe N." << n << " is THINKING\n" << flush;
    get_the_right_fork( n );
    get_the_left_fork( n );
    
    philosophe_state[n] = EATING;
    logfile << "The Philosophe N." << n << " is EATING\n" << flush;
    release_the_right_fork( n );
    release_the_left_fork( n );
    
    philosophe_state[n] = SLEEPING;
    logfile << "The Philosophe N." << n << " is SLEEPING\n" << flush;
    //sleep(1) ;
  }
}

// parallel thread for monitoring the states
void
monitor() {
  while ( true ) { // infinite loop
    std::this_thread::sleep_for(std::chrono::seconds(1)); // wait for one second
    cerr << "\nPHILOSOPHES:  ";
    for ( int i = 0 ; i < N_PHILOSOPHE ; ++i ) {
      switch ( philosophe_state[i] ) {
        case THINKING:  cerr << " T"; break;
        case EATING:    cerr << " E"; break;
        case SLEEPING:  cerr << " S"; break;
      }
    }
    cerr << "\nFORK:         ";
    for ( int i = 0 ; i < N_PHILOSOPHE ; ++i ) {
      switch ( fork_state[i] ) {
        case FREE:   cerr << " F"; break;
        case IN_USE: cerr << " U"; break;
      }
    }
    cerr << "\n";
  }
}

int
main( int argc, char *argv[] ) {

  logfile.open("Philosophes.txt");
  
  thread philosophe_thread[N_PHILOSOPHE], monitor_thread;

  std::fill( philosophe_state.begin(), philosophe_state.end(), SLEEPING );
  std::fill( fork_state.begin(), fork_state.end(), FREE );

  for ( int i = 0 ; i < N_PHILOSOPHE ; ++i ) {
    cerr << "Create Philosophe N." << i << "\n";
    philosophe_thread[i] = thread( Philosophe, i );
  }
  auto m = thread(monitor);
  m.join();
  return 0 ;
}