/*\

  implementation of power

\*/

#include "vector.h"
#include <stdio.h> // for printf
#include <stdlib.h> // for malloc and free

void
Vector_new( Vector * obj, int dim ) {
  obj->dim  = dim;
  obj->data = malloc( dim*sizeof(double) );
}

void
Vector_delete( Vector * obj ) {
  obj->dim  = 0;
  free(obj->data);
}

void
Vector_set( Vector * obj, int pos, double value ) {
  obj->data[pos] = value;
}

double
Vector_get( Vector * obj, int pos ) {
  return obj->data[pos];
}

//void Vector_addto( Vector * res, Vector const * a ); // add vector a to res
//void Vector_subto( Vector * res, Vector const * a ); // sub vector a to res
//void Vector_mult( Vector * res, double s ); // multiply res y a scalar s
//void Vector_axpy( Vector * res, Vector const * a, double s ); // multiply res += s * a

void
Vector_print( char const prefix[], Vector const * obj ) {
  printf("%s[",prefix);
  if ( obj->dim > 0 ) {
    printf("%lg",obj->data[0]);
    for ( int i = 1; i < obj->dim; ++i )
      printf(", %lg",obj->data[i]);
  }
  printf("]\n");
}

