#include "polynoms.hpp"

#include <cmath>
#include <limits>

namespace Polynoms {

  // extend the ostream class for printing the polynomial
  ostream&
  operator << ( ostream & stream, Polynom const & p ) {

    if ( p.degree <  0 ) return stream << "0";
    if ( p.degree == 0 ) return stream << p.coeffs[0];

    real_type c = p.coeffs[p.degree];
    if ( c < 0 ) stream << "- ";
    if ( c == 1 || c == -1 ) {
      // print nothing
    } else {
      stream << std::abs(c);
      if ( p.degree > 0 ) stream << " * ";
    }
    if ( p.degree > 0 ) stream << "x";
    if ( p.degree > 1 ) stream << "^" << p.degree;

    for ( int_type i=p.degree-1; i >= 0; --i ) {
      c = p.coeffs[i];
      if ( c == 1 ) {
        stream << " + ";
        if ( i == 0 ) stream << "1";
        if ( i > 0 ) stream << "x";
      } else if ( c == -1 ) {
        stream << " - ";
        if ( i == 0 ) stream << "1";
        if ( i > 0 ) stream << "x";
      } else if ( c == 0 ) {
        // skip
        continue;
      } else {
        if ( c > 0 ) stream << " + " << c;
        else         stream << " - " << -c;
        if ( i > 0 ) stream << " * x";
      }
      if ( i > 1 ) stream << "^" << i;
    }
    return stream;
  }

  ostream&
  operator << ( ostream & stream, Sturm const & p ) {
    for ( int_type i = 0; i <= p.npoly; ++i )
      stream << "S[" << i << "] = " << p.sturm[i] << '\n';
    return stream;
  }

  real_type
  Polynom::normalize() {
    real_type scale_factor = 0;
    if ( this ->degree >= 0 ) {
      for ( int_type i = 0; i <= this->degree; ++i ) {
        real_type absi = std::abs( this->coeffs[i] );
        if ( scale_factor < absi ) scale_factor = absi;
      }
      if ( scale_factor == 0 ) {
        this ->degree = -1;
      } else {
        for ( int_type i = 0; i <= this->degree; ++i )
          this->coeffs[i] /= scale_factor;
      }
    }
    return scale_factor;
  }

  Polynom &
  Polynom::purge( real_type epsi ) {
    for ( int_type i = 0; i <= this->degree; ++i ) {
      real_type absi = std::abs( this->coeffs[i] );
      if ( absi <= epsi ) this->coeffs[i] = 0;
    }
    this->adjustDegree();
    return *this;
  }

  Polynom
  operator + ( Polynom const & a, Polynom const & b ) {
    DEBUG_MESSAGE("Polynom + Polynom");
    // Polynom res(a); // copy constructor
    Polynom res = a; // copy constructor
    res += b;
    return res;
  }

  Polynom
  operator - ( Polynom const & a, Polynom const & b ) {
    DEBUG_MESSAGE("Polynom - Polynom");
    // Polynom res(a); // copy constructor
    Polynom res = a; // copy constructor
    res -= b;
    return res;
  }

  Polynom
  operator * ( Polynom const & a, Polynom const & b ) {
    DEBUG_MESSAGE("Polynom * Polynom");
    Polynom res;
    int_type d = a.degree+b.degree;
    res.allocate( d, d+1 );
    for ( int_type k = 0; k <= res.degree; ++k )
      res.coeffs[k] = 0;

    for ( int_type i = 0; i <= a.degree; ++i )
      for ( int_type j = 0; j <= b.degree; ++j )
         res.coeffs[i+j] += a.coeffs[i] * b.coeffs[j];

    return res;
  }

  void
  division( Polynom const & p,
            Polynom const & q,
            Polynom       & m,
            Polynom       & r ) {

    Polynom P(p), Q(q);

    real_type scaleP = P.normalize(); // p(x) <-P(x)/scaleP
    real_type scaleQ = Q.normalize(); // q(x) <-Q(x)/scaleQ

    Polynom R(P), M;

    M.setup( P.degree - Q.degree );

    real_type lcQ = Q.coeffs[Q.degree];
    int_type  dd  = R.degree - Q.degree;
    while ( dd >= 0 ) {
      real_type lcR = R.coeffs[R.degree];
      real_type bf  = lcR/lcQ;
      M.coeffs[dd]  = bf;
      for ( int_type j = 0; j < Q.degree; ++j )
        R.coeffs[dd+j] -= bf * Q.coeffs[j];
      --R.degree;
      --dd;
    }
    // adjust degree or remainder
    R.purge( 100*std::numeric_limits<real_type>::epsilon() );

    m = (M *= scaleP/scaleQ);
    r = (R *= scaleP);
  }

  /*

   build sturm sequence

  */
  void
  Sturm::build( Polynom const & P ) {
    Polynom M, R;

    this->allocate( P.degree+1 );
    sturm[0] = P;
    sturm[1] = P.derivative();
    npoly = 1;
    while ( true ) {
      division( sturm[npoly-1], sturm[npoly], M, R );
      if ( R.degree >= 0 ) {
        sturm[++npoly] = -R;
      } else {
        break;
      }
    }

    // divide by GCD
    for ( int_type i=0; i <= npoly; ++i ) {
      division( sturm[i], sturm[npoly], M, R );
      M.normalize();
      sturm[i] = M;
    }
  }

  /*

  compute sign changed on the sequence

  */
  int_type
  Sturm::sign_changes( real_type x ) const {
    int_type sign_var  = 0;
    int_type last_sign = 0;
    for ( int_type i = 0; i <= this->npoly; ++i ) {
      real_type v = this->sturm[i].eval( x );
      if ( v > 0 ) {
        if ( last_sign == -1 ) ++sign_var;
        last_sign = 1;
      } else if ( v < 0 ) {
        if ( last_sign == 1 ) ++sign_var;
        last_sign = -1;
      }
    }
    return sign_var;
  }

}
