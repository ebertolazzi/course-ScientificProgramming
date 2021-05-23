// I/O functions like printf, scanf etc
#include <stdio.h>

// Standard function for OS interface, exit() ...
#include <stdlib.h>

/*!
 | Search prime numbers less <= 1000
 | version 1
\*/
int // return value to the OS
main() { // main = entry point for the compiled program
  int is_prime[1001]; // define is_prime as a vector of 1001 elements]
                      // is_prime[0] ... is_prime[1000]
  int i, j, k;

  // all number are prime
  // for ( (1) INITIAL; (2) CHECK; (3) INCREMENT ) (4) STATEMENT;
  //
  // (1)
  // loop:
  // if ( not (2) ) goto exit;
  // (4); (3)
  // goto loop;
  // exit:
  //
  for ( i = 0; i <= 1000; ++i ) is_prime[i] = 1;

  // use the sieve to remove composed integer
  for ( i=2; i <= 1000; ++i ) {
    if ( is_prime[i] == 1 ) {
      // `i` is prime, remove all multiple
      for ( j=2*i; j <= 1000; j += i )
        is_prime[j] = 0;
    }
  }

  // pretty printt the result
  for ( k = i = 1; i <= 1000; ++i ) {
    if ( is_prime[i] == 1 ) {
      printf("%5d ", i);
      if ( (k % 10) == 0 ) printf("\n");
      ++k;
    }
  }
  if ( (k % 10) != 1 ) printf("\n");
  return 0;
}
