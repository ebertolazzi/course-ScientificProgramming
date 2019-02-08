#include <iostream>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cerr;
using std::setw;

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

  long vv[] = {1, 3, -1, -3, -2, 1, 4, 6, 7};
  int  nvv  = sizeof(v)/sizeof(v[0]);

  cout << "PRIMA\n";
  print( v, nv );
  std::sort( v, v+nv );
  cout << "DOPO\n";
  print( v, nv );

  cout << "PRIMA\n";
  print( vv, nvv );
  std::sort( vv, vv+nvv );
  cout << "DOPO\n";
  print( vv, nvv );

  return 0;
}
