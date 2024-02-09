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
  // define a row vector
  Eigen::MatrixXd M1, M2;
  M1.resize(5,6);
  M1 <<  1, 2, 3, 4, 5, 6,
         7, 8, 9,10,11,12,
        13,14,15,16,17,18,
        19,20,21,22,23,24,
        25,26,27,28,29,30;

  std::cout << "Matrix M1\n";
  std::cout << M1 <<'\n';

  std::cout << "\n\nSubblock M1(1:3,1:3)\n";
  //                        +-+ block dimension (3x3)
  std::cout << M1.block(0,0,3,3) <<'\n';
  //                    +-+ initial block position

  std::cout << "\n\nSubblock M1(3:5,2:5)\n";
  std::cout << M1.block(2,1,2,3) <<'\n';

  std::cout << "\n\nTOP LEFT 2x2\n";
  std::cout << M1.topLeftCorner(2,2) <<'\n';

  std::cout << "\n\nTOP LEFT 2x2 (using compile time size)\n";
  std::cout << M1.topLeftCorner<2,2>() <<'\n';

  std::cout << "\n\nTOP ROWS 2 (using compile time size)\n";
  std::cout << M1.topRows<2>() <<'\n';

  std::cout << "Thats all folks!!\n";
  return 0;
}
