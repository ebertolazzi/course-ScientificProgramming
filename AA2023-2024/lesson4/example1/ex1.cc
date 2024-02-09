/*
Example of usage of eigen3 linear algebra library

*/

// load EIGEN3 library for matrix vector operation
#include <Eigen/Core>

// standard header for I/O
#include <iostream>

// standard header C++ strings
#include <string>

// for timing
#include <chrono>

int
main() {
  // define a row vector
  Eigen::Matrix<double, 1, Eigen::Dynamic> V;
  V.resize(5);

  // initialize
  std::cout << "step 1\n";
  V(0) = 1; // access with index checking

  std::cout << "step 2\n";
  V.coeffRef(100) = 1; // no bound check

  // runtime error (bad indexing, out of allocated memory)
  //std::cout << "step 3\n";
  //V(100) = 1;

  std::cout << "step 3\n";
  V << 1, 2, 3, 4, 5;

  std::cout << "V\n" << V << '\n';

  Eigen::Matrix<double, 2, 2, Eigen::ColMajor> M22;
  M22 << 1, 2,
         3, 4;

  std::cout << "M22\n" << M22 << '\n';

  Eigen::Matrix<double, 2, 2, Eigen::RowMajor> M22b;
  M22b << 1, 2,
          3, 4;

  std::cout << "M22b\n" << M22b << '\n';

  // access row data
  for ( int i{0}; i < 4; ++i ) {
    // acces the i-th element stored the matrix
    std::cout << "M22[" << i << "]= " << M22.data()[i] << '\n';
  }
  for ( int i{0}; i < 4; ++i ) {
    // acces the i-th element stored the matrix
    std::cout << "M22b[" << i << "]= " << M22b.data()[i] << '\n';
  }

  // define a colum vector of 4 element of double
  typedef Eigen::Matrix<double, 4, 1> V4;

  // define a row vector dynamic of integer
  typedef Eigen::Matrix<int, 1, Eigen::Dynamic> Vi_row;

  V4 v4;
  Vi_row vi;

  return 0;
}
