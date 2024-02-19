
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

#include <random>

using Eigen::Matrix;
using Eigen::Dynamic;

typedef Matrix<double,Dynamic,1>       vec;
typedef Matrix<double,Dynamic,Dynamic> mat;

double epsi{0.1};

std::random_device rd;
std::mt19937       mt(rd());
std::uniform_real_distribution<double> dist(-epsi, epsi);

int
main() {

  vec x, y, b, sol;
  mat M;

  int N{1000};

  // allocate the vector to the correct size
  x.resize(N);
  y.resize(N);
  M.resize(2,2);
  b.resize(2);

  // pertub the line x+1;
  for ( int i{0}; i < N; ++i ) {
    x(i) = -10+20*double(i)/(N-1);
    y(i) = 1+100*x(i)+dist(mt); // add a perturbation [-epsi,epsi]
  }

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
