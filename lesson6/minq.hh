#pragma once

#ifndef MINQ_dot_HH
#define MINQ_dot_HH

#include <Eigen/Dense>
#include <Eigen/QR>

namespace LS {

  typedef double real_type;

  using Eigen::Matrix;
  using Eigen::Dynamic;
  using Eigen::ColPivHouseholderQR;

  typedef Matrix<double,Dynamic,1>       vec;
  typedef Matrix<double,Dynamic,Dynamic> mat;

  // prototype of the function
  bool
  minq(
    vec const & x, // X-coordinate
    vec const & y, // Y-coordinate
    real_type & A, // coeffs of y = A*x+B
    real_type & B
  );
}

#endif
