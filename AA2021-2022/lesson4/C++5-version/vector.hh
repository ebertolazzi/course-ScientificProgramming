// more efficient if the compiler known
#pragma once

// double inclusion avoiding trick
#ifndef VECTOR_dot_HH
#define VECTOR_dot_HH

#include <iostream>

// define the struct Vector
class Vector {
  int    dim;
  double *data;

public:

  // constructor
  Vector( int dim ); // allocate

  // destructor
  ~Vector();

  int get_dim() const { return dim; }

  // use operator with reference = pointer used as a value
  double &       operator [] ( int i );
  double const & operator [] ( int i ) const;

  //void addto( Vector const * a ); // add vector a to res
  Vector & operator += ( Vector const & rhs );

  void subto( Vector const * a ); // sub vector a to res
  void mult( double s ); // multiply res y a scalar s 
  void axpy( Vector const * a, double s ); // multiply res += s * a

  // grant access to the private parte of the struct
  friend std::ostream & operator << ( std::ostream & s, Vector const & obj );
};


// define the struct Vector
template <unsigned N>
class Vector2 {
  double data[N];

public:

  // constructor
  Vector2() {
    for ( int i = 0 ; i < N ; ++i ) data[i] = 0;
  }

  // destructor
  ~Vector2() {}

  int get_dim() const { return N; }

  // use operator with reference = pointer used as a value
  double &       operator [] ( int i )        { return data[i]; }
  double const & operator [] ( int i ) const  { return data[i]; }

  //void addto( Vector const * a ); // add vector a to res
  Vector2 & operator += ( Vector2 const & rhs ) {
    for ( int i = 0; i < N; ++i ) data[i] = rhs.data[i];
    return *this;
  }
};

template <unsigned DIM>
inline
std::ostream &
operator << ( std::ostream & s, Vector2<DIM> const & obj ) {
  s << "[";
  if ( DIM > 0 ) {
    s << obj[0];
    for ( int i = 1; i < DIM; ++i )
      s << ", " << obj[i];
  }
  s << "]";
  return s;
}

std::ostream &
operator << ( std::ostream & s, Vector const & obj );

// other routine in the library

#endif
