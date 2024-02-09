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

  auto odd  = Eigen::seq(1,Eigen::last,2);
  auto even = Eigen::seq(0,Eigen::last,2);

  std::cout << "Matrix M1 odd elements\n";
  std::cout << M1(odd,odd) <<'\n';

  std::cout << "Matrix M1 even elements\n";
  std::cout << M1(even,even) <<'\n';

  //M2 = M1(odd,odd);
  //M1(even,even) = M2;

  M1(even,even) = M1(odd,odd);

  std::cout << "Matrix M1 after operation\n";
  std::cout << M1 <<'\n';
  std::cout << M1(odd,odd) <<'\n';
  std::cout << M1(even,even) <<'\n';


  std::cout << "Thats all folks!!\n";
  return 0;
}
