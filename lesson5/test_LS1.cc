
#include <iostream>
#include <Eigen/Dense>

/*
  For compilation

  make  (gnumake)
  ninja
  cmake (windows/linux/osx)

  Xcode
  Visual Studio
  eclipse
  code-block (mingw)
  CLion (cmake)

*/

//using Eigen::MatrixXd;

using Eigen::Matrix;
using Eigen::Dynamic;

typedef Matrix<double,Dynamic,1>       vec;
typedef Matrix<double,Dynamic,Dynamic> mat;

int main() {

  vec x, y, b, sol;
  mat M;

  // allocate the vector to the correct size
  x.resize(10);
  y.resize(10);
  M.resize(2,2);
  b.resize(2);

  x << 1, 2, 3, 4, 5, 2, 3, 4, 1, -2;
  y << 2, 2, 2, 2, 2, 2, 2, 2, 2, 2;

  std::cout << "x = " << x.transpose() << std::endl;
  std::cout << "y = " << y.transpose() << std::endl;

  // M(0,0) = sum x^2
  M(0,0) = x.dot(x);
  // M(0,1) = M(1,0) = sum x
  M(0,1) = M(1,0) = x.sum();
  // number of points
  M(1,1) = x.size();

  // b(0) = sum x y
  b(0) = x.dot(y);

  // b(1) = sum y
  b(1) = y.sum();

  std::cout << "M\n" << M << std::endl;
  std::cout << "b\n" << b << std::endl;

  sol = M.lu().solve(b);

  std::cout << "A = " << sol(0) << std::endl;
  std::cout << "B = " << sol(1) << std::endl;

  return 0;
}
