#include "polynoms.hpp"

#include <iomanip>

using std::cout;
using std::cerr;
using std::setw;

int
main() {

  using Polynoms::real_type;
  using Polynoms::int_type;

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

    Polynoms::Sturm sturm;

    sturm.build( p );
    cout << "Sturm:\n" << sturm << '\n';

    p.clear();
    p << -45 << 156 << -197 << 104 << -15 << -4 << 1;

    real_type x[] = { -10, -8, -4, 0, 0.99, 1, 1.01, 2, 10, 20 };

    // zeros -5, 3, 3, 1, 1, 1
    cout << "P  = " << p << "\n";
    sturm.build( p );
    cout << "Sturm:\n" << sturm << '\n';

    for ( int_type k = 0; k < 10; ++k ) {
      int_type s0 = sturm.sign_changes( x[k] );
      cout << "x = " << setw(5) << x[k] << " sign var = " << s0 << '\n';
    }

  } catch ( std::exception const & e ) {
    cerr << "Exception: " << e.what() << "\n";
  } catch ( ... ) {
    cerr << "Unkown error\n";
  }
  cout << "All done Folks!\n";
  return 0;
}
