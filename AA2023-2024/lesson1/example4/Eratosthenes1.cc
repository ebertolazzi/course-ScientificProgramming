// for I/O
#include <iostream>

// use STL object vector
#include <vector>

/*!
 | Search prime numbers less <= 1000
 | version 1
\*/
int // return value to the OS
main() { // main = entry point for the compiled program
  std::vector<bool> is_prime; // define is_prime as a vector of boolean
                              // is_prime[i] == true --> i is a prime number
                              // is_prime[i] == false --> i is a NOT a prime number

  int const N{100000};
  //    ^-- tell the compiler that N cannot be modified

  // allocate memory for 1000 elements
  is_prime.resize( N+1 );

  // all number are prime (method one)
  std::fill( is_prime.begin(), is_prime.end(), true );

  // all number are prime (method two) using old C++ way
  for ( std::vector<bool>::iterator it = is_prime.begin(); it != is_prime.end(); ++it ) *it = true;

  // all number are prime (method two) using C++11 way to demand type deduction to the compiler
  for ( auto it = is_prime.begin(); it != is_prime.end(); ++it ) *it = true;

  // all number are prime (method two) using C++11 way to do the loop
  for ( bool && e : is_prime ) e = true; // must use bool & becouse I want to modify the element
  for ( auto && e : is_prime ) e = true;

  // use the sieve to remove composed integer
  // int i = 2;
  // int i{2};
  // are equivalent but the second select explicitly the costructor of the "integer" object
  for ( int i{2}; i <= N; ++i ) {
    if ( is_prime[i] ) {
      // `i` is prime, remove all multiple
      for ( int j{2*i}; j <= N; j += i )
        is_prime[j] = false;
    }
  }

  // pretty printt the result
  int const M{15}; // write a new line every M printed elements
  int       k{0};  // counter of printed prime number
  for ( int i{1}; i <= N; ++i ) {
    if ( is_prime[i] ) {
      std::cout << i << ' ';
      if ( (++k%M) == 0 ) std::cout << '\n';
    }
  }
  if ( (k%M) != 0 ) std::cout << '\n';

  std::cout << "There are " << k << " prime number in the range [1," << N << "]\n";

  std::cout << "All done folks!!\n";

  return 0;
}
