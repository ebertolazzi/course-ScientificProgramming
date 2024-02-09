/*
Example of usage of eigen3 linear algebra library

*/

// load EIGEN3 library for matrix vector operation
//#include <Eigen/Core>
#include <Eigen/Dense>

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

  // alias of Eigen::Map<Eigen::Matrix<double,3,3>>
  using MapM3 = Eigen::Map<Eigen::Matrix<double,3,3>>;

  // alias of Eigen::Map<Eigen::Matrix<double,3,1>>
  using MapV3 = Eigen::Map<Eigen::Matrix<double,3,1>>;

  // mapping memory to eiegn3 object
  double data[9+3+3];
  MapM3 M(data);
  MapV3 b(data+9);
  MapV3 x(data+9+3);

  // reallocate x to a new piece of memory
  double data2[3];
  new (&x) MapV3(data2);

  M << 4, 1, 1,
       1, 4, 1,
       1, 1, 4;
  x << 1, 2, 3;
  b = M*x;

  std::cout << "Matrix M\n" << M << "\n";
  std::cout << "Vector b^T\n" << b.transpose() << "\n";

  x.setZero();
  std::cout << "x^T\n" << x.transpose() << "\n";

  x = M.lu().solve( b );
  std::cout << "x^T\n" << x.transpose() << "\n";

  // store the LU decomposition of M.
  // The only way to do the decomposition is by the
  // constructore
  //Eigen::FullPivLU<Eigen::MatrixXd> LU(M);

  // define the class without an LU decomposition
  Eigen::FullPivLU<Eigen::MatrixXd> LU;

  // do not reallocate the object
  // but call the constructor for the class
  // in this case do the LU decomposition
  new (&LU) Eigen::FullPivLU<Eigen::MatrixXd>( M );

  x = LU.solve( b );
  std::cout << "x^T\n" << x.transpose() << "\n";

  std::cout << "Thats all folks!!\n";
  return 0;
}
