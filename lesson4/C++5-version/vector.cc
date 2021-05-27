/*\

  implementation of power

\*/

#include "vector.hh"
#include <iostream> // for printf

Vector::Vector( int dim ) {
  // can access directly the field of the struct
  // this == pointer to the struct into the call
  this->dim  = dim;
  this->data = new double[dim]; // use C++ allocator
  // initialize data
  for ( int i = 0 ; i < dim ; ++i ) this->data[i] = 0;
}

Vector::~Vector() {
  this->dim = 0;
  delete [] this->data; // use C++ allocator
  std::cout << "call Vector::~Vector\n";
}

double &
Vector::operator [] ( int pos ) {
  return this->data[pos];
}

double const &
Vector::operator [] ( int pos ) const {
  return this->data[pos];
}

Vector &
Vector::operator += ( Vector const & rhs ) {
  for ( int i = 0; i < dim; ++i )
    data[i] += rhs.data[i];
  return *this; // return reference of the struct
}

//void Vector_addto( Vector * res, Vector const * a ); // add vector a to res
//void Vector_subto( Vector * res, Vector const * a ); // sub vector a to res
//void Vector_mult( Vector * res, double s ); // multiply res y a scalar s
//void Vector_axpy( Vector * res, Vector const * a, double s ); // multiply res += s * a

std::ostream &
operator << ( std::ostream & s, Vector const & obj ) {
  s << "[";
  if ( obj.get_dim() > 0 ) {
    s << obj[0];
    for ( int i = 1; i < obj.get_dim(); ++i )
      s << ", " << obj[i];
  }
  s << "]";
  return s;
}
