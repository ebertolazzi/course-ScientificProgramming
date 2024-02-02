#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


int
main( int argc, char const * argv[] ) {

  Vector v1, v2, v3;

  Vector_new( &v1, 3 );
  Vector_new( &v2, 3 );
  Vector_new( &v3, 3 );

  Vector_set( &v1, 0, 1);
  Vector_set( &v1, 1, 1);
  Vector_set( &v1, 2, 1);

  Vector_print( "v1 = ", &v1 );
  Vector_print( "v2 = ", &v2 );
  Vector_print( "v3 = ", &v3 );

  Vector_delete( &v1 );
  Vector_delete( &v2 );
  Vector_delete( &v3 );

  printf("All done folks!\n");
  return 0;
}
