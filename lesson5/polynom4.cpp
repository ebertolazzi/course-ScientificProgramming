#include <iostream>

using namespace std;

// parameterize the integer and floating point types
typedef int    int_type;
typedef double real_type;

/*\
  Struct Polynom is a C-struct with a "method", i.e.
  a function that operate on the element of the struct
\*/

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
    this->allocate(_degree);
  }

  ~Polynom() {
    cout << "pass ~Polynom()\n" ;
    if ( this->coeffs != nullptr ) delete [] this->coeffs;
    this->coeffs = nullptr; // useless
  }

  void
  allocate( int_type degree );

  int_type
  get_degree() const
  { return degree; }

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
Polynom::allocate( int_type degree ) {
  cout << "enter Polynom::allocate( degree = " << degree << ")\n";
  // avoid memory lack, free allocated memory
  if ( this->coeffs != nullptr ) delete [] this->coeffs;
  this->degree      = degree;
  this->n_allocated = degree+1;
  this->coeffs      = new real_type[degree+1];
  cout << "exit Polynom::allocate( degree = " << degree << ")\n";
}

int
main() {
  Polynom P(4), Q, R;

  P[0] = 1;
  P[1] = -1;
  P[2] = 3;
  P[3] = 9; // call operator []
  P.operator[](4) = 2; // equivalent call but less interesting

  cout << "P = " << P << " = " << P << "\n";
  // (((cout + "P = ") + P) + "\n");

  /*
   cout <- cout << "P = "
   cout <- cout << P
   cout <- cout << "\n"

  */

  // generate error!
  P(10) = 4;


  return 0;
}
