#include <iostream>

using namespace std;

// parameterize the integer and floating point types
typedef int    int_type;
typedef double real_type;

/*\
  Struct Polynom is a C-struct with a "method", i.e.
  a function that operate on the element of the struct
\*/

typedef struct {
  int_type    n_allocated;
  int_type    degree;
  real_type * coeffs;

  void
  init();

  void
  allocate( int_type degree );

  void
  print();

} Polynom;

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
Polynom::print() {
  if ( degree < 0 ) return;
  real_type c = coeffs[degree];

  if ( c == 1 ) {
    if ( degree == 0 ) cout << "1";
  } else if ( c == -1 ) {
    if ( degree == 0 ) cout << "-1";
    else               cout << "-" ;
  } else {
    cout << c;
  }
  if ( degree > 0 ) cout << " * x";
  if ( degree > 1 ) cout << "^" << degree;

  for ( int_type i=degree-1; i >= 0; --i ) {
    c = coeffs[i];
    if ( c == 1 ) {
      cout << " + ";
      if ( i == 0 ) cout << "1";
      if ( i > 0 ) cout << "x";
    } else if ( c == -1 ) {
      cout << " - ";
      if ( i == 0 ) cout << "1";
      if ( i > 0 ) cout << "x";
    } else {
      if ( c > 0 ) cout << " + " << c;
      else         cout << " - " << -c;
      if ( i > 0 ) cout << " * x";
    }
    if ( i > 1 ) cout << "^" << i;
  }
  cout << "\n";
}

int
main() {
  Polynom P, Q, R;

  cout << "call P.init();\n";
  P.init();
  cout << "done P.init();\n";

  P.allocate(4);

  P.coeffs[0] = 1;
  P.coeffs[1] = -1;
  P.coeffs[2] = 3;
  P.coeffs[3] = 9;
  P.coeffs[4] = 2;

  P.print();

  return 0;
}
