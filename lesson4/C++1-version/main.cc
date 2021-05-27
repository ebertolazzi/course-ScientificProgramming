#include <stdio.h>
#include <stdlib.h>
#include "vector.hh"


int
main( int argc, char const * argv[] ) {

  Vector v1, v2, v3;

  v1.allocate( 3 );
  v2.allocate( 3 );
  v3.allocate( 3 );

  v1.set( 0, 1);
  v1.set( 1, 1);
  v1.set( 2, 1);

  v1.print( "v1 = " );
  v2.print( "v2 = " );
  v3.print( "v3 = " );

  v1.destroy();
  v2.destroy();
  v3.destroy();

  printf("All done folks!\n");
  return 0;
}
