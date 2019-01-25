#include <stdio.h>

// for malloc, calloc, free
#include <stdlib.h>

// contains information of the size and range of the standard C-type
// used for access INT_MAX
#include <limits.h>

// for strcmp and string manipulation
#include <string.h>

#include "bitvec.h"

//
static
void
sieve( BitVec * p_is_prime ) {
  int i, j, N;

  // all number are prime
  BitVec_allone( p_is_prime );

  // use the sieve to remove composed integer
  // N = (*p_is_prime).number_of_bits;
  N = p_is_prime->number_of_bits;
  for ( i=2; i < N; ++i ) {
    if ( BitVec_get( p_is_prime, i ) == 1 ) {
      // `i` is prime, remove all multiple
      for ( j=2*i; j < N && j > 0; j += i )
        BitVec_off( p_is_prime, j );
    }
  }
}

// pretty print the result
static
void
pretty_print( BitVec * p_is_prime ) {
  int i, k, N;
  N = p_is_prime->number_of_bits;
  for ( k = i = 1; i < N; ++i ) {
    if ( BitVec_get( p_is_prime, i ) == 1 ) {
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
  int  N, iparsed;
  char out[100];
  if ( argc != 2 ) {
    printf("command: %s N\nexpected 1 argument found %d\n",
           argv[0], argc-1);
    exit(0);
  }
  // sscanf parse the string pointed by argv[1] as integer
  // and store in N
  iparsed = sscanf(argv[1], "%d", &N );
  if ( iparsed != 1 ) {
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
  if ( N < 2 ) {
    printf("command: %s N\nN must be > 1 and <= %d, found %d\n",
           argv[0], INT_MAX, N );
    exit(0);
  }
  return N;
}

int
main( int argc, char const *argv[] ) {
  BitVec is_prime;
  int N;

  N = parse_command( argc, argv );

  // allocate memory
  BitVec_new( &is_prime, N );
  sieve( &is_prime );
  pretty_print( &is_prime );

  BitVec_delete( &is_prime );
  return 0;
}
