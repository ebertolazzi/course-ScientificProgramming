/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>

int
main() {
  Polynom P, Q, R;
  real_type cfP[] = {1,0,1,4,0};
  Polynom_New( &P, 10 );
  Polynom_Set( &P, 4, cfP );
  Polynom_Print( &P, stdout );
  return 0;
}
