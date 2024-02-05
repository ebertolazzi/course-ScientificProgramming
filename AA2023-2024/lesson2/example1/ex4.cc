/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

// templated version of the factotial

template <typename T = int>
static
T
factorial( T n ) {
  T res{1};
  for ( T i = 2; i <= n; ++i ) res *= i;
  return res;
}

int
main() {

  // capture part | arguments | body [optional]
  // []             ()          {}    -> return type
  auto fun  = []( int n ) -> int { int res{1}; for ( int i = 2; i <= n; ++i ) res *= i; return res; };

  // check if is >= C++14
  #if __cplusplus >= 201402L
  // auto in lambda function arguments is allowed for >= C++14
  auto fun1 = []( auto n ) -> decltype(n) {
    decltype(n) res{1};
    for ( decltype(n) i = 2; i <= n; ++i ) res *= i;
    return res;
  };
  #endif

  int32_t f = fun( 14 );
  std::cout << "factorial of 14 = " << f << '\n';

  // check if is >= C++14
  #if __cplusplus >= 201402L
  int32_t f1 = fun1( int32_t(14) );
  std::cout << "factorial (32 bit) of 14 = " << f1 << '\n';

  int64_t f2 = fun1( int64_t(14) );
  std::cout << "factorial (64 bit) of 14 = " << f2 << '\n';
  #endif

  std::cout << "All done Folks!!\n";

  return 0;
}

