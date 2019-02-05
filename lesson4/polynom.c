/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>

int_type
Polynom_New(
  Polynom * pP,
  int_type n_allocated
) {
  if ( n_allocated < 0 ) return -1;
  pP->degree      = -1;
  pP->n_allocated = n_allocated;
  pP->coeffs      = calloc( n_allocated, sizeof(real_type) );
  // check memory allocation
  if ( pP->coeffs == NULL ) return -2;
  return 0;
}

int_type
Polynom_Resize(
  Polynom * pP,
  int_type  n_allocated
) {
  if ( n_allocated <= pP->degree ) return -1;
  real_type * psaved = pP->coeffs;
  pP->n_allocated = n_allocated;
  pP->coeffs      = calloc( n_allocated, sizeof(real_type) );
  // check memory allocation
  if ( pP->coeffs == NULL ) return -2;
  // copy the old coeffs
  for ( int_type i = 0; i <= pP->degree; ++i )
    pP->coeffs[i] = psaved[i];
  free(psaved);
  return 0;
}

int_type
Polynom_Exchange(
  Polynom * pP,
  Polynom * pQ
) {
  int_type tmp = pP->degree; pP->degree = pQ->degree; pQ->degree = tmp;

  tmp = pP->n_allocated;
  pP->n_allocated = pQ->n_allocated;
  pQ->n_allocated = tmp;

  real_type * pp = pP->coeffs; pP->coeffs = pQ->coeffs; pQ->coeffs = pp;
  return 0;
}

/*!
  Destroy the polynomial by freeing memory
  \param ppP   pointer to a pointer variable which store the polynom
\*/
int_type
Polynom_Delete( Polynom * pP ) {
  if ( pP->coeffs != NULL ) { // avoid double free
    free( pP->coeffs );
    pP->coeffs      = NULL;
  }
  pP->n_allocated = 0;
  pP->degree      = -1; // degree of nothing is -1
  return 0;
}

/*!
\*/
int_type
Polynom_Set(
  Polynom       * pP,
  int_type        degree,
  real_type const cfs[]
) {
  int_type i;
  if ( degree < pP->n_allocated ) {
    for ( i = 0; i <= degree; ++i ) pP->coeffs[i] = cfs[i];
    // adjust the degree to the true degree
    while ( pP->coeffs[degree] == 0 && degree >= 0 ) --degree;
    pP->degree = degree;
  } else {
    return -1;
  }
  return 0;
}

int_type
Polynom_Print(
  Polynom const * pP,
  FILE          * fd
) {
  if ( pP->degree < 0 ) return -1;

  char const *fmt[] = {
    "%g",
    "%g * x",
    "%g * x^%d"
  };
  int_type k = pP->degree; if ( pP->degree > 2 ) k = 2;
  fprintf( fd, fmt[k], pP->coeffs[pP->degree], pP->degree );

  for ( int_type i=pP->degree-1; i >= 0; --i ) {
    real_type c = pP->coeffs[i];
    if      ( c < 0 ) {
      fprintf( fd, " - " );
      c = -c;
    } else if ( c > 0 ) {
      fprintf( fd, " + " );
    }
    else continue; // print nothing
    int_type k = i; if ( i > 2 ) k = 2;
    fprintf( fd, fmt[k], c, i );
  }
  fprintf( fd, "\n" );
  return 0;
}

/*!
\*/
int_type
Polynom_Assign(
  Polynom       * pP,
  Polynom const * pQ
) {
  if ( pP->n_allocated <= pQ->degree ) {
    // re-allocate if necessary
    Polynom_Resize( pP, pQ->degree+1);
  }
  pP->degree = pQ->degree;
  for ( int_type i=0; i <= pQ->degree; ++i )
    pP->coeffs[i] = pQ->coeffs[i];
  return 0;
}

/*!
\*/
int_type
Polynom_ScalarMultiply(
  Polynom * pP,
  real_type a
) {
  for ( int_type i=0; i <= pP->degree; ++i )
    pP->coeffs[i] *= a;
  return 0;
}

/*!
\*/
int_type
Polynom_AddTo(
  Polynom       * pP,
  Polynom const * pQ
) {
  if ( pP->n_allocated <= pQ->degree ) {
    // re-allocate if necessary
    Polynom_Resize( pP, pQ->degree+1);
  }
  int_type i = 0;
  if ( pP->degree <= pQ->degree ) {
    for ( ; i <= pP->degree; ++i )
      pP->coeffs[i] += pQ->coeffs[i];
    for ( ; i <= pQ->degree; ++i )
      pP->coeffs[i] = pQ->coeffs[i];
  } else {
    for ( ; i <= pQ->degree; ++i )
      pP->coeffs[i] += pQ->coeffs[i];
  }
  return 0;
}

/*!
\*/
int_type
Polynom_Axpy(
  Polynom       * pP,
  real_type       a,
  Polynom const * pQ
) {
  if ( pP->n_allocated <= pQ->degree ) {
    // re-allocate if necessary
    Polynom_Resize( pP, pQ->degree+1);
  }
  int_type i = 0;
  if ( pP->degree <= pQ->degree ) {
    for ( ; i <= pP->degree; ++i )
      pP->coeffs[i] += a*pQ->coeffs[i];
    for ( ; i <= pQ->degree; ++i )
      pP->coeffs[i] = a*pQ->coeffs[i];
  } else {
    for ( ; i <= pQ->degree; ++i )
      pP->coeffs[i] += a*pQ->coeffs[i];
  }
  return 0;
}

/*!
\*/
int_type
Polynom_GAxpy(
  Polynom       * pP,
  real_type       a,
  real_type       b,
  Polynom const * pQ
) {
  if ( pP->n_allocated <= pQ->degree ) {
    // re-allocate if necessary
    Polynom_Resize( pP, pQ->degree+1);
  }
  int_type i = 0;
  if ( pP->degree <= pQ->degree ) {
    for ( ; i <= pP->degree; ++i )
      pP->coeffs[i] = a*pP->coeffs[i] + b*pQ->coeffs[i];
    for ( ; i <= pQ->degree; ++i )
      pP->coeffs[i] = b*pQ->coeffs[i];
  } else {
    for ( ; i <= pQ->degree; ++i )
      pP->coeffs[i] += a*pP->coeffs[i] + b*pQ->coeffs[i];
  }
  return 0;
}

/*!
\*/
int_type
Polynom_Multiply(
  Polynom       * pP,
  Polynom const * pQ
) {
  int_type out_degree = pP->degree * pQ->degree;
  Polynom R;
  Polynom_New( &R, out_degree+1 );
  R.degree = out_degree;

  for ( int_type k = 0; k <= out_degree; ++k ) R.coeffs[k] = 0;

  for ( int_type i = 0; i <= pP->degree; ++i )
    for ( int_type j = 0; j <= pQ->degree; ++j )
       R.coeffs[i+j] += pP->coeffs[i] * pQ->coeffs[j];

  Polynom_Exchange( &R, pP );
  Polynom_Delete( &R );
  return 0;
}

/*!
\*/
int_type
Polynom_Division(
  Polynom const * pP,
  Polynom const * pQ,
  Polynom       * pM,
  Polynom       * pR
);

/*!
\*/
int_type
Polynom_Derivative(
  Polynom const * pP,
  Polynom       * pDP
);
