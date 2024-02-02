#include <iostream>

using namespace std;

// templated function
template <typename T>
T
do_something( T const & a ) {
  cout << "Using do_something(" << typeid(T).name() << ")\n";
  return a+1;
}

// specialization for the case T = int
template <>
int
do_something( int const & a ) {
  cout << "Using do_something( int ) specialized\n";
  return a+1;
}

// templated function
template <typename T1, typename T2>
void
do_something( T1 const & a, T2 const & b ) {
  cout << "Using do_something(" << typeid(T1).name() << ", "
                                << typeid(T2).name() << ")\n";
}

// specialization for the case T = int
template <typename T>
void
do_something( T const & a, T const & b ) {
  cout << "Using do_something(" << typeid(T).name() << " == "
                                << typeid(T).name() << ") specialized\n";
}

void
do_something( int const & a, int const & b ) {
  cout << "Using do_something( int - int ) alternative\n";
}


int // this is the tye type of return value
main() {
  int   a1   = 1;
  int   res1 = do_something(a1) ;
  float a2   = 1;
  float res2 = do_something(a2) ;
  double a3   = 1;
  double res3 = do_something(a3) ;
  unsigned long a4   = 1;
  unsigned long res4 = do_something(a4) ;

  do_something(a1,a2) ;
  do_something(a2,a4) ;
  do_something(a1,a1) ;
  do_something(a3,a3) ;

  return 0 ; // return is a statement for returning value to the caller
}
