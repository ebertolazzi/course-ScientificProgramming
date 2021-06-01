#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

pthread_mutex_t mutex_var = PTHREAD_MUTEX_INITIALIZER;

typedef struct { int numThread; } ParameterForThread;

extern "C"
void * 
PrintHello( void * thePars )
{
  // thePars contains a pointer to the data passed in the 
  // call of pthread_create (last parameter)
  ParameterForThread * pars = static_cast<ParameterForThread*>(thePars) ;
  
  unsigned sn = (rand()%3)+1 ;

  sleep(sn) ;
  
  pthread_mutex_lock(&mutex_var); // block other thread until unlock
  cerr << "\nThread n. " << pars -> numThread << " sleep = " << sn << " Hello World!\n";
  pthread_mutex_unlock(&mutex_var);

  pthread_exit(NULL); // exit and release resource for the thread
  return NULL;
}

int
main (int argc, char *argv[])
{
  pthread_t          threads[NUM_THREADS] ;
  ParameterForThread pars[NUM_THREADS] ;
 
  for ( int t = 0 ; t < NUM_THREADS ; ++t ) {
    pars[t].numThread = t;
    cout << "Creating thread N. " << t << endl ;
    int rc = pthread_create(&threads[t], // storage for thread information
                            NULL,      
                            PrintHello,  // the called thread
                            static_cast<void*>(&pars[t]) ); // data passed to the thread
    
    if ( rc ) {
      cerr << "ERROR; return code from pthread_create() is " << rc << "\n" ;
      exit(-1);
    }
  }
  
  pthread_exit(NULL); /* aspetta che the thread abbiano finito */
  
  return 0 ;
}
