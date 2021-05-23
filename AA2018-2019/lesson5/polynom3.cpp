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
  Polynom();

  // default constructor
  Polynom( int_type degree );

  void
  allocate( int_type degree );

  void
  print( ostream & stream ) const;

  // possible operator that can be defined
  // + * - / ^ % ~ > >= < <= == != () [] | & || && -> * << >> += -= /= *=
  real_type &
  operator [] ( int_type i ) const
  { return coeffs[i]; }

};

Polynom::Polynom() {
  cout << "enter Polynom::Polynom()\n";
  this->n_allocated = 0;
  this->degree      = -1;
  this->coeffs      = nullptr;
  cout << "exit Polynom::Polynom()\n";
}

Polynom::Polynom( int_type degree ) {
  cout << "enter Polynom::Polynom( degree = " << degree << ")\n";
  /*
  this->n_allocated = degree+1;
  this->degree      = degree;
  this->coeffs      = new real_type[degree+1];
  */
  this->coeffs = nullptr;
  this->allocate( degree );
  cout << "exit Polynom::Polynom( degree = " << degree << ")\n";
}
// extend the ostream class for printing the polynomial
ostream&
operator << ( ostream & stream, Polynom const & p ) {
  p.print(stream);
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

void
Polynom::print( ostream & stream ) const {
  if ( degree < 0 ) return;
  real_type c = coeffs[degree];

  if ( c == 1 ) {
    if ( degree == 0 ) stream << "1";
  } else if ( c == -1 ) {
    if ( degree == 0 ) stream << "-1";
    else               stream << "-" ;
  } else {
    stream << c;
  }
  if ( degree > 0 ) stream << " * x";
  if ( degree > 1 ) stream << "^" << degree;

  for ( int_type i=degree-1; i >= 0; --i ) {
    c = coeffs[i];
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
}

int
main() {
  Polynom P(4), Q, R;

  P[0] = 1;
  P[1] = -1;
  P[2] = 3;
  P[3] = 9; // call operator []
  P.operator[](4) = 2; // equivalent call but less interesting


  // P(2,3);

  P.print( cout );

  cout << "P = " << P << " = " << P << "\n";
  // (((cout + "P = ") + P) + "\n");

  /*
   cout <- cout << "P = "
   cout <- cout << P
   cout <- cout << "\n"

  */

  return 0;
}
