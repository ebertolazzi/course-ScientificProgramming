#include "LS.hh"

namespace LS {

  bool
  LS_QR::solve( integer N, real_type const x_ptr[], real_type const y_ptr[], real_type & a, real_type & b ) {
    m_A.resize(N,2);

    // remap memory pointed by x_ptr and y_ptr as Eigen vector
    // c++ way to force remove const to a pointer
    Eigen::Map<vec> x(const_cast<real_type*>(x_ptr),N);
    // c++11 way to force remove const to a pointer
    Eigen::Map<vec> y(std::remove_const<real_type*>::type(y_ptr),N);

    // M(0,0) = sum x^2
    m_A.col(0) = x;
    m_A.col(1).fill(1);

    // initialize the stored m_LU class using the
    // constructor of the class PartialPivLU
    // m_LU is not allocated but simply the constructor of the class is called
    new (&m_QR) Eigen::ColPivHouseholderQR<mat>( m_A );

    // solve the linear system (factored as LU)
    m_sol = m_QR.solve( y );

    a = m_sol(0);
    b = m_sol(1);

    return true;
  }

  bool
  LS_QR::solve( vec const & x, vec const & y, real_type & a, real_type & b ) {

    integer N{x.rows()};

    m_A.resize(N,2);

    // M(0,0) = sum x^2
    m_A.col(0) = x;
    m_A.col(1).fill(1);

    // initialize the stored m_LU class using the
    // constructor of the class PartialPivLU
    // m_LU is not allocated but simply the constructor of the class is called
    new (&m_QR) Eigen::ColPivHouseholderQR<mat>( m_A );

    // solve the linear system (factored as LU)
    m_sol = m_QR.solve( y );

    a = m_sol(0);
    b = m_sol(1);

    return true;
  }

}
