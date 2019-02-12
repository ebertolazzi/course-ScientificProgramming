#include <iostream>

// define prototype of external fun fortran_fun
//extern int fortran_fun( int a, float b, double c, char d );
//extern int fortran_fun( int a );

#define F77NAME(A) A##_

extern "C" double F77NAME(fortran_fun)( double * a );

extern "C" double F77NAME(fortran_fun2)( double a[], int * size );

extern "C" void F77NAME(print_string)( char const str[], int & size );


using namespace std;

namespace Pluto {

  int
  stupid_function( int a ) { return a+1; }

  int
  stupid_function( int a, int b ) { return a+b; }

}

int
main() {
  double a = 1.234;
  double b;
  double c[] = { 1,2, 3, 4};
  int    dim[] = {4,4}, str_len = 1000;
  //b = F77NAME(fortran_fun)( a, 1, 1, 'c' );
  b = F77NAME(fortran_fun)( &a );
  cout << "a = " << a << '\n';
  cout << "b = " << b << '\n';
  b = F77NAME(fortran_fun2)( c, dim );
  cout << "fortran_fun2 = " << b << '\n';

  F77NAME(print_string)( "PIPPO", str_len );

  return 0;
}
