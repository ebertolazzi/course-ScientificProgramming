/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>

int
main() {
  int_type ok = 0;
  Polynom P, Q, GCD;
  real_type cfP[] = { -1, 1, 0, 1, 1 };
  real_type cfQ[] = { -1, 2, 0, -2, 1, 1 };
  ok |= Polynom_New( &P, 10 );
  ok |= Polynom_New( &Q, 10 );
  ok |= Polynom_Init( &GCD );
  ok |= Polynom_Set( &P, 4, cfP );
  ok |= Polynom_Set( &Q, 5, cfQ );

  printf("P = "); Polynom_Print( &P, stdout );
  printf("Q = "); Polynom_Print( &Q, stdout );

  ok = Polynom_GCD( &P, &Q, &GCD );

  printf("GCD = "); Polynom_Print( &GCD, stdout );
  printf("ok = %d\n", ok);

  return 0;
}
