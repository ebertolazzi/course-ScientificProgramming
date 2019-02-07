#include <iostream>

using namespace std;

// parameterize the integer and floating point types
typedef int    int_type;
typedef double real_type;

class Polynom {
  int_type    n_allocated;
  int_type    degree;
  real_type * coeffs;

public:

  // default constructor
  Polynom()
  : n_allocated(0)
  , degree(-1)
  , coeffs(nullptr)
  {}

  // another constructor
  Polynom( int_type _degree )
  : n_allocated(0)
  , degree(_degree)
  , coeffs(nullptr)
  {
    this->setup(_degree);
  }

  ~Polynom() {
    cout << "pass ~Polynom()\n" ;
    if ( this->coeffs != nullptr ) delete [] this->coeffs;
    this->coeffs = nullptr; // useless
  }

  void
  setup( int_type degree );

  // possible operator that can be defined
  // + * - / ^ % ~ > >= < <= == != () [] | & || && -> * << >> += -= /= *=
  real_type &
  operator [] ( int_type i ) const
  { return coeffs[i]; }

  real_type &
  operator () ( int_type i ) const {
    if ( i < 0 || i > degree ) {
      cerr << "Polynom::operator () ( " << i << " ), index out of bound\n";
      exit(0);
    }
    return coeffs[i];
  }

  // p(x) = a(x)
  Polynom & operator = ( Polynom const & a );

  // p(x) = a
  Polynom & operator = ( real_type a );

  // p *= 123; ==> p(x) <- p(x)*123
  Polynom & operator *= ( real_type a );

  // p /= 123; ==> p(x) <- p(x)/123
  Polynom & operator /= ( real_type a );

  // p *= q ; ==> p(x) <- p(x)*q(x)
  Polynom & operator *= ( Polynom const & q );

  // p += q ; ==> p(x) <- p(x)+q(x)
  Polynom & operator += ( Polynom const & q );

  // p -= q ; ==> p(x) <- p(x)-q(x)
  Polynom & operator -= ( Polynom const & q );

  // p += q ; ==> p(x) <- p(x)+a
  Polynom & operator += ( real_type a );

  // p -= q ; ==> p(x) <- p(x)-a
  Polynom & operator -= ( real_type a );

  // dp(x) = p'(x) where p(x) is the "internal polynomial"
  void derivative( Polynom & dp ) const ;

  // friend operators
  // res(x) = a(x) * b(x)
  friend
  Polynom
  operator + ( Polynom const & a, Polynom const & b );

  // res(x) = a(x) - b(x)
  friend
  Polynom
  operator - ( Polynom const & a, Polynom const & b );

  // res(x) = a(x) * b(x)
  friend
  Polynom
  operator * ( Polynom const & a, Polynom const & b );

  // p(x) = m(x) * q(x) + r(x)
  friend
  void
  poly_division( Polynom const & p,
                 Polynom const & q,
                 Polynom       & m,
                 Polynom       & r );

  // now operator << can access private data
  friend
  ostream& operator << ( ostream & stream, Polynom const & p );
};

// extend the ostream class for printing the polynomial
ostream&
operator << ( ostream & stream, Polynom const & p ) {

  if ( p.degree < 0 ) return stream;

  real_type c = p.coeffs[p.degree];

  if ( c == 1 ) {
    if ( p.degree == 0 ) stream << "1";
  } else if ( c == -1 ) {
    if ( p.degree == 0 ) stream << "-1";
    else                 stream << "-" ;
  } else {
    stream << c;
  }
  if ( p.degree > 0 ) stream << " * x";
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
    } else {
      if ( c > 0 ) stream << " + " << c;
      else         stream << " - " << -c;
      if ( i > 0 ) stream << " * x";
    }
    if ( i > 1 ) stream << "^" << i;
  }
  return stream;
}

void
Polynom::setup( int_type degree ) {
  // avoid memory lack, free allocated memory
  if ( this->coeffs != nullptr ) delete [] this->coeffs;
  this->degree      = degree;
  this->n_allocated = degree+1;
  this->coeffs      = new real_type[degree+1];
}

int
main() {
  Polynom P(4), Q(4), R;

  P[0] = 1;
  P[1] = -1;
  P[2] = 3;
  P[3] = 9; // call operator []
  P[4] = 2; // equivalent call but less interesting

  Q[0] = 1;
  Q[1] = 21;
  Q[2] = -3;
  Q[3] = 9; // call operator []
  Q[4] = 1; // equivalent call but less interesting

  cout << "P = " << P << " = " << Q << "\n";

  P += Q;
  R = P*Q+R;

  // (((cout + "P = ") + P) + "\n");

  /*
   cout <- cout << "P = "
   cout <- cout << P
   cout <- cout << "\n"

  */

  return 0;
}
