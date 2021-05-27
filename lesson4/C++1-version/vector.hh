// more efficient if the compiler known
#pragma once

// double inclusion avoiding trick
#ifndef VECTOR_dot_HH
#define VECTOR_dot_HH

// define the alias of the struct Vector
typedef struct Vector Vector;

// define the struct Vector
struct Vector {
  int    dim;
  double *data;

  // Use a prefix Vector_ for all the calls involving the struct Vector
  void allocate( int dim ); // allocate
  void destroy(); // free vector
  void set( int pos, double value );
  double get( int pos );
  void addto( Vector const * a ); // add vector a to res
  void subto( Vector const * a ); // sub vector a to res
  void mult( double s ); // multiply res y a scalar s 
  void axpy( Vector const * a, double s ); // multiply res += s * a
  void print( char const prefix[] ); // print on the terminal
};

// other routine in the library

#endif
