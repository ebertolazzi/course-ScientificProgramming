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

  void
  init();

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

// extend the ostream class for printing the polynomial
ostream&
operator << ( ostream & stream, Polynom const & p ) {
  p.print(stream);
  return stream;
}

// :: = scope operator
void
Polynom::init() {
  cout << "enter Polynom::init()\n";
  n_allocated = 0;
  degree      = -1;
  coeffs      = nullptr; // nullptr == NULL
  cout << "exit Polynom::init()\n";
}

void
Polynom::allocate( int_type degree ) {
  this->degree      = degree;
  this->n_allocated = degree+1;
  this->coeffs      = new real_type[degree+1];
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
  Polynom P, Q, R;

  cout << "call P.init();\n";
  P.init();
  cout << "done P.init();\n";

  P.allocate(4);

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
