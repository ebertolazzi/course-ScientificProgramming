#include <stdio.h>
#include <stdlib.h>

/*!
 | Search prime numbers less <= 1000
 | version 1
\*/
int
main() {
  int is_prime[1001];
  int i, j, k;

  // all number are prime
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
