#include <stdio.h>

// for malloc, calloc, free
#include <stdlib.h>

// contains information of the size and range of the standard C-type
// used for access INT_MAX
#include <limits.h>

int
main( int argc, char const *argv[] ) {
  // is_prime is defined as a pointer to int
  // arithmetic of pointer:
  // *is_prime --> deference a pointer, get the content pointed by is_prime
  // ++is_prime increment the address by the size of int
  // --is_prime decrement the address by the size of int
  // is_prime + 12 add 12 * sizeof(int) byte to the addess contained in is_prime
  // *(is_prime + 5) accessing the 6th int element starting from the addess
  //                 of is_prime
  // *(is_prime + 5) == is_prime[5]
  int * is_prime;
  int i, j, k, N;

  printf("Find all prime number less than N (<= %d)\n\n",INT_MAX);
  printf("Insert N: ");

  do {
    scanf("%d", &N);
    // some check
    if ( N < 2 )
      printf("N must be > 1 and <= %d\nTry again:", INT_MAX );
  } while ( N < 2 );

  // allocate memory for N elements of size in byte sizeof(int)
  // is_prime is the pointer of the beginning of the allocated
  // memory block
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

  // free the allocated memory and return it to the OS
  free (is_prime);
  return 0;
}
