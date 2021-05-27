// more efficient if the compiler known
#pragma once

// double inclusion avoiding trick
#ifndef VECTOR_dot_H
#define VECTOR_dot_H

/*
mode 1 no typedef, use struct
struct Vector {
  int     dim;
  double *data;
};
*/

/*
mode 2 define struct then the alias Vector
struct Vector {
  int     dim;
  double *data;
};

typedef struct Vector Vector;
*/

// mode 2
typedef struct {
  int     dim;
  double *data;
} Vector;


// Use a prefix Vector_ for all the calls involving the struct Vector
extern void Vector_new( Vector * obj, int dim); // allocate
extern void Vector_delete( Vector * obj ); // free vector
extern void Vector_set( Vector * obj, int pos, double value );
extern double Vector_get( Vector * obj, int pos );
extern void Vector_addto( Vector * res, Vector const * a ); // add vector a to res
extern void Vector_subto( Vector * res, Vector const * a ); // sub vector a to res
extern void Vector_mult( Vector * res, double s ); // multiply res y a scalar s
extern void Vector_axpy( Vector * res, Vector const * a, double s ); // multiply res += s * a

extern void Vector_print( char const prefix[], Vector const * obj ); // print on the terminal

// other routine in the library

#endif
