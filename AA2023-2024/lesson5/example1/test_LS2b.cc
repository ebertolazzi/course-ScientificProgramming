
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>

#include <random>

using Eigen::Matrix;
using Eigen::Dynamic;
using Eigen::ColPivHouseholderQR;

typedef Matrix<double,Dynamic,1>       vec;
typedef Matrix<double,Dynamic,Dynamic> mat;

double epsi{0.1};

std::random_device rd;
std::mt19937       mt(rd());
std::uniform_real_distribution<double> dist(-epsi, epsi);

int main() {

  vec x, y, sol, b;
  mat M;

  int N{1000};

  // allocate the vector to the correct size
  x.resize(N);
  y.resize(N);
  M.resize(N,2);
  b.resize(N);

  // pertub the line x+1;
  for ( int i{0}; i < N; ++i ) {
    x(i) = -10+20*double(i)/(N-1);
    y(i) = 1+100*x(i)+dist(mt); // add a perturbation [-epsi,epsi]
  }

  // M(0,0) = sum x^2
  M.col(0) = x;
  M.col(1).fill(1);

  // initialize the object QR that perform QR decomoposition
  // and di QR decomposition of its argument
  ColPivHouseholderQR<mat> QR(M);

  sol = QR.solve(y);
  std::cout << "A = " << sol(0) << std::endl;
  std::cout << "B = " << sol(1) << std::endl;

  return 0;
}
