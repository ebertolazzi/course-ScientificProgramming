#include <stdio.h>
#include <stdlib.h>
#include "power.h"


int
main( int argc, char const * argv[] ) {

  double a = 1.23, res;
  int    b;

  // to compile with debug active
  // use -DDEBUG option (gcc and clang and mingw)
  // /DDEBUG for visual studio (command line)
  #if DEBUG
  {
    int i;
    // i++ -> i = i+1; (A)
    // ++i -> i = i+1; (B)
    // (A) first use i next increment
    // (B) first increment next use i
    //
    // i = 1
    // j = ++i; j = 2
    // j = i++; j = 2, i = 3
    for ( i = 0; i < argc; ++i )
      printf("arg[%d] = \"%s\"\n",i,argv[i]);
  }
  #endif

  // parse the command line
  if ( argc != 3 ) {
    fprintf( stderr, "\n\nError, command usage:\n%s base power\n\n", argv[0] );
    exit(1); // exiting with an error
  }

  // parse the base a
  if ( sscanf( argv[1], "%lf", &a ) != 1 ) {
    fprintf( stderr, "\n\nError, first argment expected a double, found \"%s\"\n\n", argv[1] );
    exit(2); // exiting with an error
  }
  // parse the base b
  if ( sscanf( argv[2], "%d", &b ) != 1 ) {
    fprintf( stderr, "\n\nError, second argment expected a int, found \"%s\"\n\n", argv[2] );
    exit(3); // exiting with an error
  }

  printf("a = %lf\n", a);
  printf("b = %d\n", b);

  // run power version 1
  mult_count = 0;
  res        = power1( a, b );
  printf("power1(%lf,%d) = %lg\n", a, b, res );
  printf("cost %d mult or div\n", mult_count );

  // run power version 2
  mult_count = 0;
  res        = power2( a, b );
  printf("power2(%lf,%d) = %lg\n", a, b, res );
  printf("cost %d mult or div\n", mult_count );

  // run power version 3
  mult_count = 0;
  res        = power3( a, b );
  printf("power1(%lf,%d) = %lg\n", a, b, res );
  printf("cost %d mult or div\n", mult_count );

  printf("All done folks!\n");
  return 0;
}
