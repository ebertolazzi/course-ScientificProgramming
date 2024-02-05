/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

// templated version of the factotial

int
main(){

  function<int64_t(int64_t)> factorial = [&factorial]( int64_t n ) -> int64_t {
    cout << "Enter factorial(" << n << ")\n";
    if ( n < 2 ) {
      cout << "Exit factorial(" << n << ")\n";
      return 1;
    }
    int64_t res = factorial(n-1)*n;
    cout << "Exit factorial(" << n << ")\n";
    return res;
  };

  int64_t n{6};
  int64_t f1 = factorial( n );
  std::cout << "factorial of " << n << " = " << f1 << '\n';

  std::cout << "All done Folks!!\n";

  return 0;
}

