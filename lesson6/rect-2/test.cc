#include <iostream>
#include "rect.hh"

int
main() {

  GEOM::rect r1(-1,-1, 1, 1), r2, r3;

  (r2 = r1).translate(1,1.2);

  r3 = r1;
  r3.translate(3,2.1);

  bool c2 = r1.collide(r2);
  bool c3 = r1.collide(r3);

  std::cout << "r1 vs r2 = " << (c2?"TRUE":"FALSE") << '\n';
  std::cout << "r1 vs r3 = " << (c3?"TRUE":"FALSE") << '\n';

  std::cout << "Add done folks\n";

  return 0;
}
