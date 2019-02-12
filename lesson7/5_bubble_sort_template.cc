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

typedef int    int_type;  // int_type is an alias of int
typedef double real_type; // real_type is an alias of float

// for rand()
#include <stdlib.h>

/*
 Bubble sort algorithm applyed to a generic type "T"

*/


template <typename Int, typename Type>
void
sort( Int n, Type v[] ) { // vector of "unknown length"
  for ( Int i = 0 ; i < n-1 ; ++i )
    for ( Int j = i+1 ; j < n ; ++j )
      if ( v[j] < v[i] )
        std::swap( v[i], v[j] ); // STL algorithm for exchange
}

template <typename T>
T
sum( T a, T b ) { // vector of "unknown length"
  return a+b;
}

template <typename T>
class Pippo {
  T data[10];
public:
  typedef T value_type;
};

int // this is the tye type of return value
main() {

  typedef Pippo<double> Class_Pippo;

  Pippo<double> a;

  Class_Pippo::value_type a_type;

  int res = sum<float>(1,1.3);

  cout << "res = " << res << '\n';

  {
    // declare v ad a vector, the size is deduced by the initialization with {}
    int           v[1000];
    unsigned long vsize = 10;

    for ( unsigned long i = 0; i < vsize; ++i )
      v[i] = rand() & 0xFF;

    // call the sort routine
    //sort( vsize, v ) ;
    sort<int,int>( vsize, v ) ;

    // cout = character out
    for ( int_type i = 0 ; i < vsize ; ++i )
      cout << "v[ " << i << "] = " << v[i] << '\n';
  }

  {
    // declare v ad a vector, the size is deduced by the initialization with {}
    float v[] = { 4, 1, -0.3f, 8.4f, 2.3, 88, 1231, 0.1212f, -1000 } ;
    int vsize = sizeof(v)/sizeof(v[0]) ;

    // call the sort routine
    sort( vsize, v ) ;

    // cout = character out
    for ( int_type i = 0 ; i < vsize ; ++i )
      cout << "v[ " << i << "] = " << v[i] << '\n';
  }

  return 0 ; // return is a statement for returning value to the caller
}
