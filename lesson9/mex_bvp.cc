/*\
:|:  A simple program that compute approximate solution of
:|:  the boundary value problem
:|:
:|:  y(x)'' + p(x) y(x)' + q(x) y(x) = r(x)
:|:  y(a) = ya
:|:  y(b) = yb
:|:
:|:  by finite difference
\*/

#include <iostream>
#include <fstream>
#include <cmath>

// from STL
#include <string>
#include <vector>

#include <Eigen/Dense>

#include "mex_utils.hh"

using namespace std ;

/*\
:|:  Parameter for the specific problem
:|:
:|:  y(x)'' + x * y(x)' - y(x) + x^2 = 0;
:|:
:|:  y(0) = 1, y(2) = 0
:|:
:|:  Exact solution
:|:
:|:         1    /1  2\   1  2   2
:|:  y(x) = - exp|- x | + - x  + -
:|:         3    \2   /   3      3
:|:
:|:                  /1  2\                 /1  (1/2)  \
:|:               exp|- x | (6 + exp(2)) erf|- 2      x|
:|:                  \2   /                 \2         /
:|:             - --------------------------------------
:|:                             / (1/2)\
:|:                        3 erf\2     / exp(2)
:|:
\*/

#if 0
  virtual real_type p( real_type x ) const = 0;
  virtual real_type q( real_type x ) const = 0;
  virtual real_type r( real_type x ) const = 0;
  virtual real_type exact( real_type x ) const { return 0; }

  }

  vec const & get_solution() const { return sol; }

};


  BVPP::real_type a  = 0;
  BVPP::real_type ya = 1;
  BVPP::real_type b  = 2;
  BVPP::real_type yb = 0;

#endif

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#define MEX_ERROR_MESSAGE \
"Usage: [L,D,U,rhs] = build_bvp( a, b, ya, yb, N )\n" \
"\n" \
"where\n" \
" [a,b] = domain of the solution\n" \
" ya    = left boundary condition\n" \
" yb    = right boundary condition\n" \
" N     = number of interval\n\n" \
" output:\n" \
" L,D,U = tridiagonal system\n" \
" rhs   = right hand side of the linear system\n"

typedef double real_type;

static
real_type
p( real_type x ) { return x; }

static
real_type
q( real_type x ) { return -1; }

static
real_type
r( real_type x ) { return x*x;}

extern "C"
void
mexFunction( int nlhs, mxArray       *plhs[],
             int nrhs, mxArray const *prhs[] ) {
  // the first argument must be a string
  try {
    if ( nlhs != 4 || nrhs != 5 ) throw MEX_ERROR_MESSAGE;

    #define CMD "[L,D,U,rhs] = build_bvp( a, b, ya, yb, N ): "

    real_type a  = getScalarValue( arg_in_0, CMD "a expected a real scalar" );
    real_type b  = getScalarValue( arg_in_1, CMD "b expected a real scalar" );
    real_type ya = getScalarValue( arg_in_2, CMD "ya expected a real scalar" );
    real_type yb = getScalarValue( arg_in_3, CMD "yb expected a real scalar" );
    int64_t   N  = getInt( arg_in_4, CMD "N expected a scalar integer" );

    MEX_ASSERT(
      a < b,
      CMD << "bad interval [a = " << a << ", b = " << b << "]"
    );

    MEX_ASSERT(
      N > 2 && N <= 1000000,
      CMD << "bad N = " << N << " N must be in [3,1000000]"
    );

    /*
    Build the coefficient of the tridiagonal matrix
    for the problem

    // first row

        |  1       0              0        0        0  |
        |  beta(1) alpha(1) gamma(1)       0        0  |
    T = |        0  beta(2) alpha(2) gamma(2)       0  |
        |        0        0  beta(3) alpha(3) gamma(3) |
        |        0        0        0                1  |


    b = [ omega(1)-beta(1)*ya, omega(2),...., omega(n-1), omega(n)-gamma(n)*yb ]^T ;

    alpha(k)   = -2/h^2 + q(x[k+1])
    beta (k)   = 1/h^2 + p(x[k+1])/(2h)
    gamma(k)   = 1/h^2 - p(x[k+1])/(2h)
    omega(k)   = r(x[k+1])
    */

    typedef Eigen::Matrix<real_type,Eigen::Dynamic,1> vec;
    vec alpha, beta, gamma, omega;

    real_type h = (b-a)/(N-1);

    // initialize the vectors
    alpha . resize(N);
    beta  . resize(N);
    gamma . resize(N);
    omega . resize(N);

    // fill the vector alpha and omega
    int64_t n = N-1;
    for ( int64_t k = 0 ; k <= n ; ++k ) {
      real_type xk = a+k*h;
      real_type pk = p(xk);
      alpha(k) = -2/(h*h) + q(xk);
      beta(k)  = 1/(h*h) - pk/(2*h);
      gamma(k) = 1/(h*h) + pk/(2*h);
      omega(k) = r(xk);
    }
    alpha(0)  = 1;
    gamma(0)  = 0;
    alpha(n)  = 1;
    beta(n)   = 0;
    omega(0)  = ya;
    omega(n)  = yb;

    real_type * L = createMatrixValue( arg_out_0, 1, N );
    real_type * D = createMatrixValue( arg_out_1, 1, N );
    real_type * U = createMatrixValue( arg_out_2, 1, N );
    real_type * R = createMatrixValue( arg_out_3, 1, N );

    for ( int64_t k = 0; k < N; ++k ) {
      L[k] = beta(k);
      D[k] = alpha(k);
      U[k] = gamma(k);
      R[k] = omega(k);
    }

  } catch ( char const msg[] ) {
    mexErrMsgTxt(msg);
  } catch ( string const & msg ) {
    mexErrMsgTxt(msg.c_str());
  } catch ( ... ) {
    mexErrMsgTxt("unknown error");
  }

}
