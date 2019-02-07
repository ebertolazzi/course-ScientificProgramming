/*
 * manipulation of polynomial of arbitrary order
 */

#include "polynom.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int_type
Polynom_Init( Polynom * pP ) {
  pP->degree      = -1;
  pP->n_allocated = 0;
  pP->coeffs      = NULL;
  return 0;
}

int_type
Polynom_New( Polynom * pP, int_type n_allocated ) {
  if ( n_allocated < 0 ) return -1;
  pP->degree      = -1;
  pP->n_allocated = n_allocated;
  pP->coeffs      = calloc( n_allocated, sizeof(real_type) );
  // check memory allocation
  if ( pP->coeffs == NULL ) return -2;
  return 0;
}

/*!

\*/
int_type
Polynom_Normalize( Polynom * pP, real_type * scale_factor ) {
  // search max module coeff
  int_type  ok = 0;
  real_type mv = 0;
  for ( int_type i = 0; i <= pP->degree; ++i ) {
    real_type absi = fabs( pP->coeffs[i] );
    if ( mv < absi ) mv = absi;
  }
  *scale_factor = mv ;
  if ( mv == 0 ) {
    ok         = -1;
    pP->degree = -1;
  } else {
    for ( int_type i = 0; i <= pP->degree; ++i )
      pP->coeffs[i] /= mv;
  }
  return ok;
}

/*!

\*/
int_type
Polynom_Purge( Polynom * pP, real_type epsi ) {
  for ( int_type i = 0; i <= pP->degree; ++i ) {
    real_type absi = fabs( pP->coeffs[i] );
    if ( absi <= epsi ) pP->coeffs[i] = 0;
  }
  return Polynom_AdjustDegree( pP );
}

/*!

\*/
int_type
Polynom_AdjustDegree( Polynom * pP ) {
  while ( pP->degree >= 0 && pP->coeffs[pP->degree] == 0 )
    --pP->degree;
  return 0;
}

int_type
Polynom_Resize( Polynom * pP, int_type  n_allocated ) {
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
Polynom_Swap( Polynom * pP, Polynom * pQ ) {
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
    pP->coeffs = NULL;
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
    pP->degree = degree;
    return Polynom_AdjustDegree( pP );
  }
  return -1;
}

int_type
Polynom_Print( Polynom const * pP, FILE * fd ) {
  if ( pP->degree < 0 ) return -1;

  char const *fmt[] = {
    "%g",
    "%g * x",
    "%g * x^%d"
  };
  int_type k = pP->degree; if ( pP->degree > 2 ) k = 2;
  real_type c = pP->coeffs[pP->degree];

  if ( ( c == 1 || c == -1 ) && k > 0 ) {
    if ( c < 0 ) fprintf( fd, "- " );
    fprintf( fd, fmt[k]+5, pP->degree );
  } else {
    fprintf( fd, fmt[k], c, pP->degree );
  }

  for ( int_type i=pP->degree-1; i >= 0; --i ) {
    c = pP->coeffs[i];
    if ( c < 0 ) {
      fprintf( fd, " - " );
      c = -c;
    } else if ( c > 0 ) {
      fprintf( fd, " + " );
    } else {
      continue; // print nothing
    }
    int_type k = i; if ( i > 2 ) k = 2;
    if ( c == 1 && k > 0 ) {
      fprintf( fd, fmt[k]+5, i );
    } else {
      fprintf( fd, fmt[k], c, i );
    }
  }
  fprintf( fd, "\n" );
  return 0;
}

/*!
\*/
int_type
Polynom_Copy( Polynom * pP, Polynom const * pQ ) {
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
Polynom_ScalarMultiply( Polynom * pP, real_type a ) {
  for ( int_type i=0; i <= pP->degree; ++i )
    pP->coeffs[i] *= a;
  return 0;
}

/*!
\*/
int_type
Polynom_AddTo( Polynom * pP, Polynom const * pQ ) {
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
  Polynom       * pR,
  Polynom const * pP,
  Polynom const * pQ
) {
  pR->degree = pP->degree + pQ->degree;
  Polynom_New( pR, pR->degree+1 );

  for ( int_type k = 0; k <= pR->degree; ++k )
    pR->coeffs[k] = 0;

  for ( int_type i = 0; i <= pP->degree; ++i )
    for ( int_type j = 0; j <= pQ->degree; ++j )
       pR->coeffs[i+j] += pP->coeffs[i] * pQ->coeffs[j];

  return 0;
}
/*!
\*/
int_type
Polynom_MultiplyTo(
  Polynom       * pP,
  Polynom const * pQ
) {
  Polynom R;
  Polynom_Init( &R );
  int_type ok = Polynom_Multiply( &R, pP, pQ );
  Polynom_Swap( &R, pP );
  Polynom_Delete( &R );
  return ok;
}

/*!

  sa * P(x) = sb * Q(x) * M(x) + R(x)
\*/
int_type
Polynom_Division(
  Polynom const * pP,
  Polynom const * pQ,
  Polynom       * pM,
  Polynom       * pR
) {
  int_type ok;
  real_type scaleP, scaleQ, scaleR;
  Polynom P, Q, M, R;
  Polynom_Init( &P );
  Polynom_Init( &Q );
  ok |= Polynom_Copy( &P, pP );
  ok |= Polynom_Copy( &Q, pQ );
  ok |= Polynom_Normalize( &P, &scaleP ); // p(x) <-P(x)/scaleP
  ok |= Polynom_Normalize( &Q, &scaleQ ); // q(x) <-Q(x)/scaleQ
  ok = Polynom_New( &R, P.degree+1 );
  if ( ok != 0 ) return -1;
  ok = Polynom_Copy( &R, &P );
  if ( ok != 0 ) return -2;
  ok = Polynom_New( &M, P.degree-Q.degree+1 );
  if ( ok != 0 ) return -3;
  M.degree = P.degree-Q.degree;
  real_type lcQ = Q.coeffs[Q.degree];
  int_type  dd  = R.degree - Q.degree;
  while ( dd >= 0 ) {
    real_type lcR = R.coeffs[R.degree];
    real_type bf  = lcR/lcQ;
    M.coeffs[dd]  = bf;
    for ( int_type j = 0; j < Q.degree; ++j )
      R.coeffs[dd+j] -= bf * Q.coeffs[j];
    --R.degree;
    --dd;
  }
  // adjust degree or remainder
  Polynom_Purge( &R, 100*DBL_EPSILON );
  Polynom_AdjustDegree( &R );

  // scale back polinomials
  // p(x) = q(x)*M(x)+r(x)/scaleR
  // P(x)/scaleP = Q(x)/scaleQ*M(x)+r(x)/scaleR
  // P(x) = Q(x)*(scaleP/scaleQ)*M(x)+R(x)*(scaleP/scaleR)

  Polynom_ScalarMultiply( &M, scaleP/scaleQ );
  Polynom_ScalarMultiply( &R, scaleP );

  ok = Polynom_Copy( pM, &M );
  if ( ok != 0 ) return -4;
  ok = Polynom_Copy( pR, &R );
  if ( ok != 0 ) return -5;
  return 0;
}

/*!
\*/
int_type
Polynom_Derivative( Polynom const * pP, Polynom * pDP ) {
  int_type ok = Polynom_New( pDP, pP->degree );
  pDP->degree = pP->degree-1;
  if ( ok != 0 ) return -1;
  for ( int_type k = 1; k <= pP->degree; ++k )
    pDP->coeffs[k-1] = pP->coeffs[k]*k;
  return 0;
}

/*!
  Given P(x) Q(x) compute G.C.D
\*/

int_type
Polynom_GCD(
  Polynom const * pP,
  Polynom const * pQ,
  Polynom       * pGCD
) {
  real_type dummy;
  Polynom M, R;
  int_type ok;
  Polynom const * pPP = pP->degree >= pQ->degree ? pP : pQ ;
  Polynom const * pQQ = pP->degree < pQ->degree ? pP : pQ ;

  Polynom_Init(&M);
  Polynom_Init(&R);
  ok = Polynom_Division( pPP, pQQ, &M, &R );
  //printf("\n\n\nPASSA GCD\n");
  //printf( "P = "); Polynom_Print( pPP, stdout );
  //printf( "Q = "); Polynom_Print( pQQ, stdout );
  //printf( "M = "); Polynom_Print( &M, stdout );
  //printf( "R = "); Polynom_Print( &R, stdout );

  if ( R.degree >= 0 ) {
    ok |= Polynom_GCD( pQQ, &R, pGCD );
  } else {
    ok |= Polynom_Copy( pGCD, pQQ );
  }

  ok |= Polynom_Normalize( pGCD, &dummy );

  Polynom_Delete( &M );
  Polynom_Delete( &R );
  return ok;
}
