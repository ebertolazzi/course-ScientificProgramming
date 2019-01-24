#include <stdio.h>
#include <stdlib.h>

/*!
 | Search prime numbers less <= 1000
 | version 2
\*/

#define NMAX 100000

int
main() {
  int is_prime[NMAX+1];
  int i, j, k, N;

  printf("Find all prime number less than N (<= 100000)\n\n");
  printf("Insert N: ");

  do {
    scanf("%d", &N);
    // some check
    if ( N < 2 || N > NMAX )
      printf("N must be > 1 and <= %d\nTry again:", NMAX );
  } while ( N < 2 || N > NMAX );

  // all number are prime
  for ( i = 0; i <= N; ++i ) is_prime[i] = 1;

  // use the sieve to remove composed integer
  for ( i=2; i <= N; ++i ) {
    if ( is_prime[i] == 1 ) {
      // `i` is prime, remove all multiple
      for ( j=2*i; j <= N; j += i )
        is_prime[j] = 0;
    }
  }

  // pretty printt the result
  for ( k = i = 1; i <= N; ++i ) {
    if ( is_prime[i] == 1 ) {
      printf("%6d ", i);
      if ( (k % 10) == 0 ) printf("\n");
      ++k;
    }
  }
  if ( (k % 10) != 1 ) printf("\n");
  return 0;
}
