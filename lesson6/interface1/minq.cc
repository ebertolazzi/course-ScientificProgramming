
#include "minq.hh"

namespace LS {

  bool
  minq(
    vec const & x, // X-coordinate
    vec const & y, // Y-coordinate
    real_type & A, // coeffs of y = A*x+B
    real_type & B
  ) {
    vec sol;
    mat M;
    int npts = x.size();

    if ( npts < 2         ) return false;
    if ( y.size() != npts ) return false;

    M.resize(npts,2);

    // M(0,0) = sum x^2
    M.col(0) = x;
    M.col(1).fill(1);

    // initialize the object QR that perform QR decomoposition
    // and di QR decomposition of its argument
    ColPivHouseholderQR<mat> QR(M);

    sol = QR.solve(y);
    A = sol(0);
    B = sol(1);
    return true;
  }

}
