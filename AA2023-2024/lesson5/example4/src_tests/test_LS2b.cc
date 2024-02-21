
#include "LS.hh"
#include <random>

LS::real_type epsi{0.1};

std::random_device rd;
std::mt19937       mt(rd());
std::uniform_real_distribution<double> dist(-epsi, epsi);

int
main() {

  LS::integer N{1000};

  LS::real_type a, b;
  LS::vec x, y;

  // allocate the vector to the correct size
  x.resize(N);
  y.resize(N);

  // pertub the line x+1;
  for ( LS::integer i{0}; i < N; ++i ) {
    x(i) = -10+20*double(i)/(N-1);
    y(i) = 1+100*x(i)+dist(mt); // add a perturbation [-epsi,epsi]
  }

  LS::LS_QR ls;

  bool ok = ls.solve( x, y, a, b );

  std::cout << "A = " << a << std::endl;
  std::cout << "B = " << b << std::endl;

  return 0;
}
