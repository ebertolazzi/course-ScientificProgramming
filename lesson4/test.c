/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>

int
main() {
  int_type ok;
  Polynom P, Q, R, M, DP;
  // p := x^5+x^4+x
  real_type cfP[] = {0,1,0,0,1,1};
  // q := x^2+x-1;
  real_type cfQ[] = {-1,1,1};
  ok = Polynom_New( &P, 10 );     printf("Polynom_New( &P, 10 ) ok = %d\n",ok);
  ok = Polynom_Set( &P, 5, cfP ); printf("Polynom_Set( &P, 5, cfP ) ok = %d\n",ok);
  ok = Polynom_New( &Q, 10 );     printf("Polynom_New( &Q, 10 ) ok = %d\n",ok);
  ok = Polynom_Set( &Q, 2, cfQ ); printf("Polynom_Set( &Q, 2, cfQ ) ok = %d\n",ok);
  ok = Polynom_Init( &R );        printf("Polynom_Init( &R ) ok = %d\n",ok);
  ok = Polynom_Init( &M );        printf("Polynom_Init( &M ) ok = %d\n",ok);
  ok = Polynom_Init( &DP );       printf("Polynom_Init( &DP ) ok = %d\n",ok);

  printf("P = ");
  Polynom_Print( &P, stdout );

  printf("Q = ");
  Polynom_Print( &Q, stdout );

  ok = Polynom_Division( &P, &Q, &M, &R ); printf("Polynom_Division( &P, &Q, &M, &R ) ok = %d\n",ok);

  printf("R = ");
  Polynom_Print( &R, stdout );

  printf("M = ");
  Polynom_Print( &M, stdout );

  ok = Polynom_Derivative( &P, &DP ); printf("Polynom_Derivative( &P, &DP ); ok = %d\n",ok);

  printf("P' = ");
  Polynom_Print( &DP, stdout );

  return 0;
}
