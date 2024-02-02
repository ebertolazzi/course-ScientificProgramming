#include <stdio.h>
#include <stdlib.h>
#include "vector.hh"


int
main( int argc, char const * argv[] ) {

  Vector v1(3), v2(3), v3(3);

  v1[0] = 1;
  v1[1] = 7;
  v1[2] = 2;

  //v1.operator[] (0) = 1;
  //v1.operator[] (1) = 2;
  //v1.operator[] (2) = 3;

  v1.print( "v1 = " );
  v2.print( "v2 = " );
  v3.print( "v3 = " );

  printf("All done folks!\n");
  return 0;
}
