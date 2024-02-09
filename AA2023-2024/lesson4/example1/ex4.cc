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

// look at
// https://eigen.tuxfamily.org/dox/group__TutorialBlockOperations.html

int
main() {
  // slicing
  Eigen::MatrixXd M1, M2;
  M1.resize(6,6);
  M2.resize(3,3);
  M1 <<  1, 2, 3, 4, 5, 6,
         7, 8, 9,10,11,12,
        13,14,15,16,17,18,
        19,20,21,22,23,24,
        25,26,27,28,29,30,
        31,32,33,34,35,36;

  std::cout << "Matrix M1\n";
  std::cout << M1 <<'\n';

  auto right = Eigen::seq(1,Eigen::last);
  auto left  = Eigen::seq(0,Eigen::last-1);

  M1(Eigen::all,right) = M1(Eigen::all,left);
  //M1(Eigen::all,right) = M1(Eigen::all,left).eval();

  std::cout << "Matrix M1 shifted\n";
  std::cout << M1 <<'\n';

  Eigen::MatrixXd A, B, C;
  Eigen::MatrixXd A22, B22;
  A22.resize(2,2);
  B22.resize(2,2);
  A.resize(20,20);
  B.resize(20,20);
  C.resize(20,20);
  A22 << 1,2,
         2,1;
  B22 << 1,3,
        -1,1;

  A.topLeftCorner<2,2>() = A22;
  B.topLeftCorner<2,2>() = B22;

  C = A*B;

  std::cout
    << "A\n" << A.topLeftCorner<2,2>()
    << "\nB\n" << B.topLeftCorner<2,2>()
    << "\nC\n" << C.topLeftCorner<2,2>();

  B = A*B;
  std::cout << "\nA*B\n" << B.topLeftCorner<2,2>() << "\n";

  B.noalias() = A*B;
  std::cout << "\nA*B\n" << B.topLeftCorner<2,2>() << "\n";

  std::cout << "Thats all folks!!\n";
  return 0;
}
