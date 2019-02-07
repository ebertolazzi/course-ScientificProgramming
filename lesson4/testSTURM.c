/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>

int
main() {
  int_type ok = 0;
  Polynom P, DP, GCD, M, R;
  real_type cfP[] = { -45, 156, -197, 104, -15, -4, 1 };
  ok |= Polynom_New( &P,  10 );
  ok |= Polynom_Init( &M );
  ok |= Polynom_Init( &R );
  ok |= Polynom_Init( &DP );
  ok |= Polynom_Init( &GCD );
  ok |= Polynom_Set( &P, 6, cfP );
  ok |= Polynom_Derivative( &P, &DP );

  printf("P = "); Polynom_Print( &P, stdout );
  printf("DP = "); Polynom_Print( &DP, stdout );

  ok = Polynom_Division( &P, &DP, &M, &R );
  printf("M = "); Polynom_Print( &M, stdout );
  printf("R = "); Polynom_Print( &R, stdout );
  ok = Polynom_GCD( &P, &DP, &GCD );
  printf("GCD = "); Polynom_Print( &GCD, stdout );
  printf("ok = %d\n", ok);

  return 0;
}
