/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>

int
main() {
  int_type ok = 0, ns;
  Polynom P, STURM[10];
  real_type x[] = { -10, -8, -4, 0, 0.99, 1, 1.01, 2, 10, 20 };
  real_type cfP[] = { -45, 156, -197, 104, -15, -4, 1 };
  // zeros -5, 3, 3, 1, 1, 1
  ok |= Polynom_New( &P, 10 );
  ok |= Polynom_Set( &P, 6, cfP );

  Polynom_Print( "P  = ", &P, "\n", stdout );

  ok = Polynom_STURM( &P, STURM, &ns );

  for ( int_type i = 0; i <= ns; ++i )
    Polynom_Print("S = ", &STURM[i], "\n", stdout) ;

  for ( int_type k = 0; k < 10; ++k ) {
    int_type s0 = Polynom_SIGN_VARIATION( x[k], STURM, ns );
    printf("x = %10g, sign var = %d\n", x[k], s0 );
  }

  return 0;
}
