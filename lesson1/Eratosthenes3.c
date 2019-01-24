#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int
main( int argc, char const *argv[] ) {
  int * is_prime;
  int i, j, k, N, M;

  printf("Find all prime number less than N (<= %d)\n\n",INT_MAX);
  printf("Insert N: ");

  do {
    scanf("%d", &N);
    // some check
    if ( N < 2 )
      printf("N must be > 1 and <= %d\nTry again:", INT_MAX );
  } while ( N < 2 );

  // allocate memory
  is_prime = calloc( N, sizeof(int));

  // check allocation
  if ( is_prime == NULL ) {
    printf("Allocation of %d integers failed:", N );
    exit(0);
  } else {
    printf("Allocated %d integers.\n", N );
  }

  // all number are prime
  for ( i = 0; i < N; ++i ) is_prime[i] = 1;

  // use the sieve to remove composed integer
  M = (int) floor(sqrt( (double)N )) ;
  printf("Start loop %d.\n", M );
  for ( i=2; i < N; ++i ) {
    if ( is_prime[i] == 1 ) {
      // `i` is prime, remove all multiple
      for ( j=2*i; j < N && j > 0; j += i )
        is_prime[j] = 0;
    }
  }

  printf("End loop\n" );
  // pretty print the result
  for ( k = i = 1; i < N; ++i ) {
    if ( is_prime[i] == 1 ) {
      printf("%6d ", i);
      if ( (k % 10) == 0 ) printf("\n");
      ++k;
    }
  }
  if ( (k % 10) != 1 ) printf("\n");

  free (is_prime);
  return 0;
}
