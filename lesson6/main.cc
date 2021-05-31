#include <iostream>
#include "minq.hh"

int main() {

  LS::real_type A, B;
  LS::vec       x, y;

  // allocate the vector to the correct size
  x.resize(10);
  y.resize(10);

  x << 1, 2, 3, 4, 5, 2, 3, 4, 1, -2;
  y << 2, 2, 2, 2, 2, 2, 2, 2, 2, 2;

  LS::minq( x, y, A, B );

  std::cout << "A = " << A << std::endl;
  std::cout << "B = " << B << std::endl;

  return 0;
}
