#include "mex_utils.hh"
#include "minq.hh"

namespace LS {

  extern "C" // is a C function
  void
  mexFunction(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    // [A,B] = minq( x, y )
    // check the number of argument
    MEX_ASSERT( nrhs == 2, "minq, expected 2 inputs, nrhs = " << nrhs << '\n' );
    MEX_ASSERT( nlhs == 2, "minq, expected 2 output, nlhs = " << nlhs << '\n' );
    // read the parameters
    mwSize dimx, dimy;
    real_type const * x = getVectorPointer(
      arg_in_0, dimx, "minq(x,y), x must be a vector"
    );
    real_type const * y = getVectorPointer(
      arg_in_1, dimy, "minq(x,y), y must be a vector"
    );
    MEX_ASSERT(
      dimx == dimy,
      "minq(x,y), length(x) = " << dimx <<
      " must be equal to length(y) = " << dimy << "\n"
    );
    MEX_ASSERT(
      dimx > 1,
      "minq(x,y), length(x) = " << dimx << " must be greather than 1\n"
    );

    // build Eigen Vector and copy data into the new allocated vectors
    vec X, Y;
    X.resize( dimx );
    Y.resize( dimy );
    std::copy_n( x, dimx, X.data() );
    std::copy_n( y, dimy, Y.data() );

    // solve LS problem
    real_type A, B;
    minq( X, Y, A, B );

    // copy solution to MATLAB return variable
    setScalarValue( arg_out_0, A );
    setScalarValue( arg_out_1, B );

  }

}
