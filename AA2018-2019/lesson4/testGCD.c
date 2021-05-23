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

  Polynom_Print( "P  = ", &P, "\n", stdout );
  Polynom_Print( "DP = ", &DP, "\n", stdout );
  printf("\n\n");

  ok = Polynom_Division( &P, &DP, &M, &R );
  Polynom_Print( "M = ", &M, "\n", stdout );
  Polynom_Print( "R = ", &R, "\n", stdout );
  ok = Polynom_GCD( &P, &DP, &GCD );
  Polynom_Print( "GCD = ", &GCD, "\n", stdout );
  printf("\n\n");
  printf("ok = %d\n", ok);

  ok = Polynom_Division( &P, &GCD, &M, &R );
  Polynom_Print( "P/GCD           = ", &M, "\n", stdout );
  Polynom_Print( "remainder P/GCD = ", &R, "\n", stdout );
  printf("\n\n");
  ok = Polynom_Division( &DP, &GCD, &M, &R );
  Polynom_Print( "DP/GCD           = ", &M, "\n", stdout );
  Polynom_Print( "remainder DP/GCD = ", &R, "\n", stdout );
  printf("\n\n");

  return 0;
}
