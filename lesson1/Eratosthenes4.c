#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

static
void
sieve( int is_prime[], int N ) {
  int i, j, M;

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
}

// pretty print the result
static
void
pretty_print( int is_prime[], int N ) {
  int i, k;
  for ( k = i = 1; i < N; ++i ) {
    if ( is_prime[i] == 1 ) {
      printf("%6d ", i);
      if ( (k % 10) == 0 ) printf("\n");
      ++k;
    }
  }
  if ( (k % 10) != 1 ) printf("\n");
}

static
int
parse_command( int argc, char const *argv[] ) {
  int  N, ierr;
  char out[100];
  if ( argc != 2 ) {
    printf("command: %s N\nexpected 1 argument found %d\n",
           argv[0], argc-1);
    exit(0);
  }
  ierr = sscanf(argv[1], "%d", &N );
  if ( ierr != 1 ) {
    printf("command: %s N\nN must be > 1 and <= %d, found N = %s\n",
           argv[0], INT_MAX, argv[1] );
    exit(0);
  }
  sprintf(out,"%d",N);
  if ( strcmp( out, argv[1] ) != 0 ) {
    printf("command: %s %s\nconverted argument as N = %d != %s\n",
           argv[0], argv[1], N, argv[1] );
    exit(0);
  }
  if ( ierr != 1 ) {
    printf("command: %s N\nN must be > 1 and <= %d, found N = %s\n",
           argv[0], INT_MAX, argv[1] );
    exit(0);
  }

  if ( N < 2 ) {
    printf("command: %s N\nN must be > 1 and <= %d, found %d\n",
           argv[0], INT_MAX, N );
    exit(0);
  }
  return N;
}

int
main( int argc, char const *argv[] ) {
  int * is_prime;
  int N;

  N = parse_command( argc, argv );

  // allocate memory
  is_prime = calloc( N, sizeof(int));

  // check allocation
  if ( is_prime == NULL ) {
    printf("Allocation of %d integers failed:", N );
    exit(0);
  } else {
    printf("Allocated %d integers.\n", N );
  }

  sieve( is_prime, N );
  pretty_print( is_prime, N );

  free (is_prime);
  return 0;
}
