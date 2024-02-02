#include "Sieve.hh"

// return the vector with the prime number
std::vector<int>
Sieve( int N ) {
  std::vector<bool> is_prime( N + 1); // working vector to filter the prime number

  // initialize the vector
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

  // create a temporary for return the result
  std::vector<int> res;
  for ( int i{2}; i <= N; ++i ) {
    if ( is_prime[i] ) res.push_back( i );
  }
  return res; // a temporary copy is done by the compiler
}

// std::vector<int> const &
// &      pass by reference to avid copy of the vector
// const  vector is not modified inside
// std::basic_ostream<char> base class for cout and more
void
Sieve_print( std::vector<int> const & primes, std::basic_ostream<char> & s, int M ) {
  // pretty printt the result
  int k{0};
  for ( const auto & e : primes ) {
    s << e << ' ';
    if ( (++k%M) == 0 ) s << '\n';
  }
  if ( (k%M) != 0 ) s << '\n';
}
