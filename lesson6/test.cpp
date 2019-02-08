#include "polynoms.hpp"

using std::cout;
using std::cerr;

int
main() {

  Polynoms::Polynom p, q, r, s, m;

  try {
    p << 1 << 2 << 3 << 4 << 5 << 6;
    ((q << 3) << -2) << 1;

    cout << "p(x) = " << p << "\n";
    cout << "q(x) = " << q << "\n";
    p += q;
    cout << "(p += q) = " << p << "\n";

    p *= q;
    cout << "(p *= q) = " << p << "\n";

    division( p, q, m, r );

    cout << "\np = " << p
         << "\nq = " << q
         << "\nm = " << m
         << "\nr = " << r
         << "\n\n";

    cout << "\nm = " << m.purge( 1e-14)
         << "\nr = " << r.purge( 1e-14)
         << "\n\n";

    // p(200000000) = 23; // out of allocated memory
    // p[200000000] = 23; // out of allocated memory

  } catch ( std::exception const & e ) {
    cerr << "Exception: " << e.what() << "\n";
  } catch ( ... ) {
    cerr << "Unkown error\n";
  }
  cout << "All done Folks!\n";
  return 0;
}
