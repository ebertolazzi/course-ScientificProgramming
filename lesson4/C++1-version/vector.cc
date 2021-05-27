/*\

  implementation of power

\*/

#include "vector.hh"
#include <stdio.h> // for printf
#include <stdlib.h> // for malloc and free

void
Vector::allocate( int dim ) {
  // can access directly the field of the struct
  // this == pointer to the struct into the call
  this->dim  = dim;
  this->data = (double *)malloc( dim*sizeof(double) );
}

void
Vector::destroy() {
  this->dim = 0;
  free(this->data);
}

void
Vector::set( int pos, double value ) {
  this->data[pos] = value;
}

double
Vector::get( int pos ) {
  return this->data[pos];
}

//void Vector_addto( Vector * res, Vector const * a ); // add vector a to res
//void Vector_subto( Vector * res, Vector const * a ); // sub vector a to res
//void Vector_mult( Vector * res, double s ); // multiply res y a scalar s
//void Vector_axpy( Vector * res, Vector const * a, double s ); // multiply res += s * a

void
Vector::print( char const prefix[] ) {
  printf("%s[",prefix);
  if ( this->dim > 0 ) {
    printf("%lg",this->data[0]);
    for ( int i = 1; i < this->dim; ++i )
      printf(", %lg",this->data[i]);
  }
  printf("]\n");
}
