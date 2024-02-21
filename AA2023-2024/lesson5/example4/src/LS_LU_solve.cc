#include "LS.hh"

#include <type_traits>

namespace LS {

  bool
  LS::solve( integer N, real_type const x_ptr[], real_type const y_ptr[], real_type & a, real_type & b ) {
    m_A.resize(2,2);
    m_b.resize(2);

    // c++ way to force remove const to a pointer
    Eigen::Map<vec> x(const_cast<real_type*>(x_ptr),N);
    // c++11 way to force remove const to a pointer
    Eigen::Map<vec> y(std::remove_const<real_type*>::type(y_ptr),N);

    // A(0,0) = sum x^2
    m_A(0,0) = x.dot(x);
    // A(0,1) = A(1,0) = sum x
    m_A(0,1) = m_A(1,0) = x.sum();
    // number of points
    m_A(1,1) = x.size();

    // b(0) = sum x y
    m_b(0) = x.dot(y);

    // b(1) = sum y
    m_b(1) = y.sum();

    // initialize the stored m_LU class using the
    // constructor of the class PartialPivLU
    // m_LU is not allocated but simply the constructor of the class is called
    new (&m_LU) Eigen::PartialPivLU<mat>( m_A );

    // in alternatove m_LU is a pointer
    //
    // m_LU = new Eigen::PartialPivLU<mat>( m_A );
    //
    // but new now perform a new allocation of the class

    // solve the linear system (factored as LU)
    m_sol = m_LU.solve( m_b );

    a = m_sol(0);
    b = m_sol(1);

    return true;
  }

  bool
  LS::solve( vec const & x, vec const & y, real_type & a, real_type & b ) {
    m_A.resize(2,2);
    m_b.resize(2);

    // A(0,0) = sum x^2
    m_A(0,0) = x.dot(x);
    // A(0,1) = A(1,0) = sum x
    m_A(0,1) = m_A(1,0) = x.sum();
    // number of points
    m_A(1,1) = x.size();

    // b(0) = sum x y
    m_b(0) = x.dot(y);

    // b(1) = sum y
    m_b(1) = y.sum();

    // initialize the stored m_LU class using the
    // constructor of the class PartialPivLU
    // m_LU is not allocated but simply the constructor of the class is called
    new (&m_LU) Eigen::PartialPivLU<mat>( m_A );

    // in alternatove m_LU is a pointer
    //
    // m_LU = new Eigen::PartialPivLU<mat>( m_A );
    //
    // but new now perform a new allocation of the class

    // solve the linear system (factored as LU)
    m_sol = m_LU.solve( m_b );

    a = m_sol(0);
    b = m_sol(1);

    return true;
  }

}
