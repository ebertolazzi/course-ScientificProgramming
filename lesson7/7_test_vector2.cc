#include <iostream>
#include <iomanip> // include objects for manipulators

#include <algorithm>
#include <vector> // include objects for manipulators

#include <cstdint>
#include <stdlib.h> // for qsort

using namespace std;


#include "TimeMeter.hh" // class computing elapsed time


// general random numer generator
template <typename U>
inline
U random() { return rand() ; }

// specialization for uint32_t (32 bit integer)
template <>
inline
uint32_t random<uint32_t>() {
  return uint32_t(rand()) ^ (uint32_t(rand())<<16) ;
}

// specialization for uint64_t (64 bit integer)
template <>
inline
uint64_t random<uint64_t>() {
  return uint64_t(rand()) ^
         (uint64_t(rand())<<16) ^
         (uint64_t(rand())<<32) ^
         (uint64_t(rand())<<48) ;
}


using namespace std ; // "include" all the items of namespace std

template <typename T>
void
print( char const name[], vector<T> const & v ) {
  typename vector<T>::const_iterator ip = v.begin();
  for ( int i = 0; ip != v.end(); ++ip, ++i )
    cout << name << "[ " << i << "] = " << *ip << '\n';
}

#include <unistd.h>

typedef struct {
  int a;
  int b;
  float data[10];
} a_struct;

ostream &
operator << ( ostream & stream, a_struct const & a ) {
  stream << a.a << " -- " << a.b;
  return stream;
}

bool
operator < ( a_struct const & a, a_struct const & b ) {
  if ( a.a < b.a ) return true;
  if ( a.a == b.a && a.b < b.b ) return true;
  return false;
}

static
int
compare_struct( a_struct const * pa, a_struct const * pb) {
  if ( pa->a == pb->a ) {
    if ( pa->b == pb->b ) return 0;
    if ( pa->b < pb->b ) return -1;
  } else if ( pa->a < pb->a ) {
    return -1;
  }
  return 1;
}

static
int
compare_int( int const * pa, int const * pb) {
  if ( *pa < *pb ) return -1 ;
  if ( *pa > *pb ) return +1 ;
  return 0 ;
}

int // this is the tye type of return value
main() {

  TimeMeter tm;

  vector<a_struct> a, b;
  int N = 100000;
  double ms;

  a.clear();     // empty the vector
  a.reserve( size_t(N) ) ; // reserve memory for N elements
  for ( int i = 0 ; i < N ; ++i ) {
    a_struct tmp;
    tmp.a = random<int>();
    tmp.b = random<int>();
    a.push_back( tmp );
  }

  b = a;

  // call STL sort routine
  tm.start();
  std::sort( a.begin(), a.end() );
  ms = tm.milliseconds();

  cout << "Sorting time (C++) = " << ms << "ms\n" ;

  // PFUN e un "alias" del tipo funzione restituisce int 2 argoment puntatore a void
  typedef int (*PFUN) (const void *,const void *);

  cout << "b size " << b.size() << '\n';

  tm.start();
  qsort( &b.front(), b.size(), sizeof(b[0]), reinterpret_cast<PFUN>(compare_struct) ) ;
  ms = tm.milliseconds();
  cout << "Sorting time (C) = " << ms << "ms\n" ;

  a.resize(10);
  print( "a", a );

  return 0;
}
