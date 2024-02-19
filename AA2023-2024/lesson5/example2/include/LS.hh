#pragma once

// avoid double inclusion
#ifndef LS_HH
#define LS_HH

#include <iostream>
#include <Eigen/Dense>

namespace LS {

  using real_type = double;
  using integer   = Eigen::Index;

  using Eigen::Matrix;
  using Eigen::Dynamic;

  typedef Matrix<real_type,Dynamic,1>       vec; // dynamic Eigen vector
  typedef Matrix<real_type,Dynamic,Dynamic> mat; // dynamic Eigen matrix

  // solve the least square problem using classical algorithm
  class LS {
    // stored problem
    vec m_b, m_sol;
    mat m_A;
    Eigen::PartialPivLU<mat> m_LU;
  public:
    LS() {}
    bool solve( integer N, real_type const x[], real_type const y[], real_type & a, real_type & b );
    bool solve( vec const & x, vec const & y, real_type & a, real_type & b );
  };

  // solve the least square problem using QR decomposition
  class LS_QR {
    // stored problem
    vec m_sol;
    mat m_A;
    Eigen::ColPivHouseholderQR<mat> m_QR;
  public:
    LS_QR() {}
    bool solve( integer N, real_type const x[], real_type const y[], real_type & a, real_type & b );
    bool solve( vec const & x, vec const & y, real_type & a, real_type & b );
  };

}

#endif