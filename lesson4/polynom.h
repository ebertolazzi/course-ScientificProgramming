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
  Allocate memory for the polynomial
  \param pP          pointer variable which store the polynom
  \param n_allocated how many coeffs are allocated
\*/
int_type
Polynom_New(
  Polynom * pP,
  int_type  n_allocated
);

int_type
Polynom_Resize(
  Polynom * pP,
  int_type  n_allocated
);

int_type
Polynom_Exchange(
  Polynom * pP,
  Polynom * pQ
);

/*!
  Destroy the polynomial by freeing memory
  \param pP   pointer variable which store the polynom
\*/
int_type
Polynom_Delete( Polynom * pP );

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
Polynom_Assign(
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
\*/
int_type
Polynom_GAxpy(
  Polynom       * pP,
  real_type       a,
  real_type       b,
  Polynom const * pQ
);

/*!
\*/
int_type
Polynom_Multiply(
  Polynom       * pP,
  Polynom const * pQ
);

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

#endif
