#include <iostream>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cerr;
using std::setw;

void
sort( int vec[], int size ) {
  for ( int i = 0; i < size-1; ++i )
    for ( int j = i+1; j < size; ++j )
      if ( vec[i] > vec[j] )
        std::swap( vec[i], vec[j] );
}

void
print( int vec[], int size ) {
  for ( int i = 0; i < size-1; ++i )
    cout << "v[ " << i << "] = " << vec[i] << '\n';
}

template <typename T>
void
scambio( T & a, T & b ) {
  T c(a) ; a = b; b = c;
}

template <typename T>
void
sort( T vec[], int size ) {
  for ( int i = 0; i < size-1; ++i )
    for ( int j = i+1; j < size; ++j )
      if ( vec[i] > vec[j] )
        scambio( vec[i], vec[j] );
}

template <typename T>
void
print( T vec[], int size ) {
  for ( int i = 0; i < size-1; ++i )
    cout << "v[ " << i << "] = " << vec[i] << '\n';
}

int
main() {

  int v[] = {1, 3, -1, -3, -2, 1, 4, 6, 7};
  int nv  = sizeof(v)/sizeof(v[0]);

  float vv[] = {1, 3, -1, -3, -2, 1, 4, 6, 7};
  int   nvv  = sizeof(v)/sizeof(v[0]);

  cout << "PRIMA\n";
  print( v, nv );
  sort( v, nv );
  cout << "DOPO\n";
  print( v, nv );
/*
  cout << "PRIMA\n";
  print( vv, nvv );
  sort( vv, nvv );
  cout << "DOPO\n";
  print( vv, nvv );
*/
  return 0;
}
