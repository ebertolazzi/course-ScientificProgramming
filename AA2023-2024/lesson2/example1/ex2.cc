/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>

using namespace std;

static
int
factorial( int n ) {
  int res{1};
  for ( int i = 2; i <= n; ++i ) res *= i;
  return res;
}

int
main(){

  int f = factorial( 6 );

  std::cout << "factorial of 6 = " << f << '\n';

  std::cout << "All done Folks!!\n";

  return 0;
}

