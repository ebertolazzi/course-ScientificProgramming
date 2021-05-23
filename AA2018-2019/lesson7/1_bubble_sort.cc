// to compile on unix/OSX use
// g++ example1.cc
// On windows with Visual Studio type
// cl.exe 1_bubble_sort.cc
//

/*
 A simple example: bubble sort
*/

// include header for C++ I/O
// search iostream in standard C++ include directory e.g. /usr/include
#include <iostream>
#include <iomanip> // include objects for manipulators
using namespace std ; // "include" all the items of namespace std

typedef int   int_type;  // int_type is an alias of int
typedef float real_type; // real_type is an alias of float

// static // sort is not exported for external linking
void // nothing to return
sort( int_type  n,      // first argument is an integer (the lenght of the vector)
      real_type v[] ) { // vector of "unknown length"
  for ( int_type i = 0 ; i < n-1 ; ++i )
    for ( int_type j = i+1 ; j < n ; ++j )
      if ( v[j] < v[i] )
        { real_type tmp = v[i] ; v[i] = v[j] ; v[j] = tmp ; }
}

typedef bool (*PFUN)(real_type,real_type) ;

// Overloading permits to declare another sort routine with "different arguments"!
void // nothing to return
sort( int_type n,      // first argument is an integer (the lenght of the vector)
      real_type    v[],    // vector of "unknown length"
      bool (*less_than)(real_type,real_type) ) {
      // you can use PFUN less_than instead of bool (*less_than)(real_type,real_type)
 
  for ( int_type i = 0 ; i < n-1 ; ++i )
    for ( int_type j = i+1 ; j < n ; ++j )
      if ( less_than(v[j],v[i]) ) {
        real_type tmp = v[i] ; v[i] = v[j] ; v[j] = tmp ;
      }
}

bool
comparator( real_type a, real_type b )
{ return a > b ; }

int
C_comparator(const void * a, const void * b) {
  real_type A = *((real_type*)a) ;
  real_type B = *((real_type*)b) ;
  if ( A < B ) return -1 ;
  if ( A > B ) return +1 ;
  return 0 ;
}

int // this is the tye type of return value
main() {

  // declare v ad a vector, the size is deduced by the initialization with {}
  real_type v[] = { 4, 1, -0.3, 8.4, 2.3, 88, 1231, 0.1212, -1000 } ;
  int_type vsize = sizeof(v)/sizeof(v[0]) ;
  
  cout << "vsize             = " << vsize             << '\n' ;
  cout << "sizeof(v)         = " << sizeof(v)         << '\n' ;
  cout << "sizeof(v[0])      = " << sizeof(v[0])      << '\n' ;
  cout << "sizeof(real_type)    = " << sizeof(real_type)    << '\n' ;
  cout << "sizeof(double)    = " << sizeof(double)    << '\n' ;
  cout << "sizeof(long int)  = " << sizeof(long int)  << '\n' ;
  cout << "sizeof(short int) = " << sizeof(short int) << '\n' ;
  
  // call the sort routine
  //sort( vsize, v ) ;

  // call the sort routine
  sort( vsize, v, comparator ) ;

  // call the C standard routine for ordering
  int ok = heapsort(v, vsize, sizeof(v[0]), C_comparator );

  // cout = character out
  for ( int_type i = 0 ; i < vsize ; ++i )
    cout << "v[ " << i << "] = " << v[i] << '\n' ;

  return 0 ; // return is a statement for returning value to the caller
}
