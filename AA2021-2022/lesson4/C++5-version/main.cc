#include <stdio.h>
#include <stdlib.h>
#include "vector.hh"


int
main( int argc, char const * argv[] ) {

  Vector     v1(3), v2(3), v3(3);
  Vector2<3> w1, w2, w3;

  v1[0] = 1;
  v1[1] = 7;
  v1[2] = 2;

  w1[0] = 1;
  w1[1] = 7;
  w1[2] = 2;

  //v1.operator[] (0) = 1;
  //v1.operator[] (1) = 2;
  //v1.operator[] (2) = 3;

  // v1.data = nullptr; cant modify private data!

  std::cout << "v1 = " << v1 << '\n';
  std::cout << "v2 = " << v2 << '\n';
  std::cout << "v3 = " << v3 << '\n';
  v2 += v1;
  std::cout << "2+v1 = " << v2 << '\n';

  std::cout << "w1 = " << w1 << '\n';
  std::cout << "w2 = " << w2 << '\n';
  std::cout << "w3 = " << w3 << '\n';
  w2 += w1;
  std::cout << "w2+w1 = " << w2 << '\n';

  printf("All done folks!\n");
  return 0;
}
