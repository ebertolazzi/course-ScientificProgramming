
#include "LS.hh"

int main() {

  LS::real_type a, b;
  LS::vec x, y;

  // allocate the vector to the correct size
  x.resize(10);
  y.resize(10);

  x << 1, 2, 3, 4, 5, 2, 3, 4, 1, -2;
  y << 2, 2, 2, 2, 2, 2, 2, 2, 2, 2;

  std::cout << "x = " << x.transpose() << std::endl;
  std::cout << "y = " << y.transpose() << std::endl;

  LS::LS ls;

  bool ok = ls.solve( x, y, a, b );

  std::cout << "A = " << a << std::endl;
  std::cout << "B = " << b << std::endl;

  return 0;
}
