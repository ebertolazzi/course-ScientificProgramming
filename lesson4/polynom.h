/*
 * manipulation of polynomial of arbitrary order
 */

#ifndef POLYNOM_H
#define POLYNOM_H

#include <stdio.h>

// parameterize the integer and floating point types
typedef int    int_type;
typedef double real_type;

/*\
::: Define the type Polynom which contains the
::: description of a polynomial
\*/

typedef struct {
  int_type    n_allocated;
  int_type    degree;
  real_type * coeffs;
} Polynom;

/*\
:::
::: Functions that operate on the polynomials
:::
::: 1)  New    (create a polynomial structure, allocate memory)
::: 2)  Delete (destroy a polynomia structure, free memory)
::: 3)  Print  (print a polynomial on stdout)
::: 4)  Set             p(x)
::: 5)  Assign          p(x) <- q(x)
::: 6)  ScalarMultiply  p(x) <- a * p(x)
::: 7)  AddTo           p(x) += q(x)
::: 8)  Axpy            p(x) += b*q(x)
::: 9)  GAxpy           p(x) <- a*p(x)+b*q(x)
::: 10) Multiply        p(x) <- p(x)*q(x)
::: 11) Division        p(x)/q(x) => p(x) = q(x)*m(x)+r(x) -> m(x), r(x)
::: 12) Derivative      q(x) <- p'(x)
:::
::: return 0  = all ok
:::        <0 = some error
\*/

// use DOXYGEN structured comments
/*!
  Initialize a polynomial "object" (no allocation)
  \param pP pointer variable which store the polynom
\*/
int_type
Polynom_Init( Polynom * pP );

/*!
  Allocate memory for the polynomial
  \param pP          pointer variable which store the polynom
  \param n_allocated how many coeffs are allocated
\*/
int_type
Polynom_New( Polynom * pP, int_type n_allocated );

/*!
  Re-allocate memory for the polynomial
  \param pP          pointer variable which store the polynom
  \param n_allocated how many coeffs are allocated
\*/
int_type
Polynom_Resize( Polynom * pP, int_type n_allocated );

/*!
  Exchange the polynomial P and Q
  \param pP  pointer variable which store the polynom
  \param pQ  pointer variable which store the polynom
\*/
int_type
Polynom_Swap( Polynom * pP, Polynom * pQ );

/*!
  Destroy the polynomial by freeing memory
  \param pP   pointer variable which store the polynom
\*/
int_type
Polynom_Delete( Polynom * pP );

/*!

\*/
int_type
Polynom_Normalize( Polynom * pP, real_type * scale_factor );

/*!

\*/
int_type
Polynom_Purge( Polynom * pP, real_type epsi );

/*!

\*/
int_type
Polynom_AdjustDegree( Polynom * pP );

/*!
\*/
int_type
Polynom_Set(
  Polynom       * pP,
  int_type        degree,
  real_type const cfs[]
);

/*!
  Pretty print the polynomial
  \param pP    pointer to the store the polynom
  \param fd    file descriptor where the polynom is written
               ( fd = stdout )
\*/
int_type
Polynom_Print(
  Polynom const * pP,
  FILE          * fd
);

/*!
\*/
int_type
Polynom_Copy(
  Polynom       * pP,
  Polynom const * pQ
);

/*!
\*/
int_type
Polynom_ScalarMultiply(
  Polynom * pP,
  real_type a
);

/*!
 Sum two polynonials
\*/
int_type
Polynom_Add(
  Polynom       * pR,
  Polynom const * pP,
  Polynom const * pQ
);

/*!
 Sum two polynonials
 R(x) = a*P(x) + b*Q(x)
\*/
int_type
Polynom_GAdd(
  Polynom       * pR,
  real_type       a,
  Polynom const * pP,
  real_type       b,
  Polynom const * pQ
);

/*!
\*/
int_type
Polynom_AddTo(
  Polynom       * pP,
  Polynom const * pQ
);

/*!
\*/
int_type
Polynom_Axpy(
  Polynom       * pP,
  real_type       a,
  Polynom const * pQ
);

/*!
 P(x) = a*P(x) + b*Q(x)
\*/
int_type
Polynom_GAxpy(
  Polynom       * pP,
  real_type       a,
  real_type       b,
  Polynom const * pQ
);

/*!
  R(x) = P(x)*Q(x)
\*/
int_type
Polynom_Multiply(
  Polynom       * pR,
  Polynom const * pP,
  Polynom const * pQ
);

/*!
  P(x) = P(x)*Q(x)
\*/
int_type
Polynom_MultiplyTo(
  Polynom       * pP,
  Polynom const * pQ
);

/*!
  P(x)/Q(x) -->  P(x) = Q(x)*M(x) + R(x)
\*/
int_type
Polynom_Division(
  Polynom const * pP,
  Polynom const * pQ,
  Polynom       * pM,
  Polynom       * pR
);

/*!
  R(x) = P'(x)
\*/
int_type
Polynom_Derivative(
  Polynom const * pP,
  Polynom       * pR
);

/*!
  Given P(x) Q(x) compute G.C.D
\*/
int_type
Polynom_GCD(
  Polynom const * pP,
  Polynom const * pQ,
  Polynom       * pGCD
);

/*!
  Given P(x) Q(x) compute G.C.D
\*/
int_type
Polynom_STURM(
  Polynom const * pP,
  Polynom         STURM[]
);

/*!
  Given P(x) Q(x) compute G.C.D
\*/
int_type
Polynom_SIGN_VARIATION( Polynom STURM[] );

#endif
