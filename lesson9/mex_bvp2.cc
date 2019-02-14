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

#include <exception>

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
"Usage: [T,rhs] = build_bvp( a, b, ya, yb, N, P, Q, R )\n" \
"\n" \
"where\n" \
" [a,b] = domain of the solution\n" \
" ya    = left boundary condition\n" \
" yb    = right boundary condition\n" \
" N     = number of interval\n\n" \
" P,Q,R = funxtion of y'' + P y' + Q y = R\n\n" \
" output:\n" \
" T   = tridiagonal matrix\n" \
" rhs = right hand side of the linear system\n"

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

    if ( nlhs != 2 || nrhs != 8 ) throw MEX_ERROR_MESSAGE;

    #define CMD "[T,rhs] = build_bvp1( a, b, ya, yb, N, P, Q, R ): "

    real_type a  = getScalarValue( arg_in_0, CMD "a expected a real scalar" );
    real_type b  = getScalarValue( arg_in_1, CMD "b expected a real scalar" );
    real_type ya = getScalarValue( arg_in_2, CMD "ya expected a real scalar" );
    real_type yb = getScalarValue( arg_in_3, CMD "yb expected a real scalar" );
    int64_t   N  = getInt( arg_in_4, CMD "N expected a scalar integer" );

    MEX_ASSERT( mxIsChar(arg_in_5), "P must be a string" );
    MEX_ASSERT( mxIsChar(arg_in_6), "Q must be a string" );
    MEX_ASSERT( mxIsChar(arg_in_7), "R must be a string" );

    string P = mxArrayToString(arg_in_5);
    string Q = mxArrayToString(arg_in_6);
    string R = mxArrayToString(arg_in_7);

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

      mxArray *args_in[1];
      mxArray *args_out[1];
      setScalarValue( args_in[0], xk );
      int ok = mexCallMATLAB( 1, args_out, 1, args_in, P.c_str() );
      MEX_ASSERT( ok == 0, CMD << "failed the call p(" << xk << ")" );

      real_type pk = getScalarValue( args_out[0], "out P(x) expected a real scalar" );

      ok = mexCallMATLAB( 1, args_out, 1, args_in, Q.c_str() );
      MEX_ASSERT( ok == 0, CMD << "failed the call q(" << xk << ")" );

      real_type qk = getScalarValue( args_out[0], "out P(x) expected a real scalar" );

      ok = mexCallMATLAB( 1, args_out, 1, args_in, R.c_str() );
      MEX_ASSERT( ok == 0, CMD << "failed the call r(" << xk << ")" );

      real_type rk = getScalarValue( args_out[0], "out P(x) expected a real scalar" );

      alpha(k) = -2/(h*h) + qk;
      beta(k)  = 1/(h*h) - pk/(2*h);
      gamma(k) = 1/(h*h) + pk/(2*h);
      omega(k) = rk;
    }
    alpha(0)  = 1;
    gamma(0)  = 0;
    alpha(n)  = 1;
    beta(n)   = 0;
    omega(0)  = ya;
    omega(n)  = yb;

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, 3*N-2 );
    real_type * J = createMatrixValue( args[1], 1, 3*N-2 );
    real_type * V = createMatrixValue( args[2], 1, 3*N-2 );
    setScalarValue( args[3], N );
    setScalarValue( args[4], N );

    real_type * RHS = createMatrixValue( arg_out_1, N, 1 );

    int64_t nnz = 0;
    for ( int64_t k = 0; k < N; ++k ) {
      I[nnz] = J[nnz] = k+1;
      V[nnz] = alpha(k);
      ++nnz;
      RHS[k] = omega(k);
    }
    for ( int64_t k = 0; k < N-1; ++k ) {
      I[nnz] = k+2; J[nnz] = k+1; V[nnz] = beta(k+1); ++nnz;
      I[nnz] = k+1; J[nnz] = k+2; V[nnz] = gamma(k);  ++nnz;
    }

    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, CMD << "failed the call sparse(...)" );

  } catch ( exception const & err ) {
    mexErrMsgTxt(err.what());
  } catch ( char const msg[] ) {
    mexErrMsgTxt(msg);
  } catch ( string const & msg ) {
    mexErrMsgTxt(msg.c_str());
  } catch ( ... ) {
    mexErrMsgTxt("unknown error");
  }

}
