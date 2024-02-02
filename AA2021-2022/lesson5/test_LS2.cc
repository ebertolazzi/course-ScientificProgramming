
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>

using Eigen::Matrix;
using Eigen::Dynamic;
using Eigen::ColPivHouseholderQR;

typedef Matrix<double,Dynamic,1>       vec;
typedef Matrix<double,Dynamic,Dynamic> mat;

int main() {

  vec x, y, sol;
  mat M;

  // allocate the vector to the correct size
  x.resize(10);
  y.resize(10);
  M.resize(10,2);

  x << 1, 2, 3, 4, 5, 2, 3, 4, 1, -2;
  y << 2, 2, 2, 2, 2, 2, 2, 2, 2, 2;

  std::cout << "x = " << x.transpose() << std::endl;
  std::cout << "y = " << y.transpose() << std::endl;

  // M(0,0) = sum x^2
  M.col(0) = x;
  M.col(1).fill(1);

  std::cout << "M\n" << M << std::endl;

  // initialize the object QR that perform QR decomoposition
  // and di QR decomposition of its argument
  ColPivHouseholderQR<mat> QR(M);

  sol = QR.solve(y);
  std::cout << "A = " << sol(0) << std::endl;
  std::cout << "B = " << sol(1) << std::endl;

  return 0;
}
