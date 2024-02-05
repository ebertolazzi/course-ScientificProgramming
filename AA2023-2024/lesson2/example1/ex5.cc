/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr{4,3,2,2,-1,45,-45,3,-3};

int
main() {

  // C-like loop
  //                 int(    ) --> convert unsigned long -> int
  for ( int i=0; i < int(arr.size()); ++i )
    cout << "arr[" << i << "] = " << arr[i] << '\n';

  // C++ old style
  for ( vector<int>::const_iterator it = arr.begin(); it != arr.end(); ++it )
    cout << "arr[" << it-arr.begin() << "] = " << *it << '\n';

  // C++11 with old style
  for ( auto it = arr.begin(); it != arr.end(); ++it )
    cout << "arr[" << it-arr.begin() << "] = " << *it << '\n';

  // more C++11 like
  int ipos{0};
  for ( auto const & v : arr ) {
    cout << "arr[" << ipos++ << "] = " << v << '\n';
  }

  sort( arr.begin(), arr.end() );

  // more C++11 like
  cout << "SORTED\n";
  ipos = 0;
  for ( auto const & v : arr ) {
    cout << "arr[" << ipos++ << "] = " << v << '\n';
  }

  std::cout << "All done Folks!!\n";

  return 0;
}

