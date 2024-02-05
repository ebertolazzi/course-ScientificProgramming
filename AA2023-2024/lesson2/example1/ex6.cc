/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T1, typename T2>
class PAIR {
public:
  T1 first;
  T2 second;
  //friend bool operator < ( PAIR<T1,T2> const & a,  PAIR<T1,T2> const & b );
};

template <typename T1, typename T2>
inline
bool operator < ( PAIR<T1,T2> const & a, PAIR<T1,T2> const & b ) {
  if ( a.first < b.first ) return true;
  if ( b.first < a.first ) return false;
  if ( a.second < b.second ) return true;
  return false;
}

vector<PAIR<int,string>> arr{
  {4,"pippo"}, {2,"pluto"}, {2,"paperino"}, {-4,"zorro"}, {-3,"duffy"},
  {4,"pappo"}, {2,"plato"}, {2,"paperino"}, {-4,"zarro"}, {-3,"duck"},
  {4,"pippa"}, {2,"plauto"}, {2,"peperino"}, {-4,"zuppo"}, {-3,"merda"}
};

int
main() {

  // more C++11 like
  int ipos{0};
  for ( auto const & v : arr )
    cout << "arr[" << ipos++ << "] = { " << v.first << "," << v.second << "}\n";

  // sort( arr.begin(), arr.end() );
  // if >= C++14
  // auto comparator = []( auto const & a, auto const & b )->bool {
  auto comparator = []( PAIR<int,string> const & a, PAIR<int,string> const & b )->bool {
    if ( a.first  < b.first ) return true;
    if ( b.first  < a.first ) return false;
    if ( a.second < b.second ) return true;
    return false;
  };
  sort( arr.begin(), arr.end(), comparator );

  // more C++11 like
  cout << "SORTED\n";
  ipos = 0;
  for ( auto const & v : arr )
    cout << "arr[" << ipos++ << "] = { " << v.first << "," << v.second << "}\n";

  std::cout << "All done Folks!!\n";

  return 0;
}

