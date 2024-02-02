
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

int main()
{
  //MatrixXd m(2,2);
  Matrix<float,Dynamic,Dynamic> m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
}
