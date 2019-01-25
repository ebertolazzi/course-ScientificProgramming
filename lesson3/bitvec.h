// standard controlled size integer
#include <stdint.h>

// avoid double inclusion trick
#ifndef BITVEC_H
#define BITVEC_H

#if 0
struct _bitvec {
  // pointer to a vector of integer which store the bits
  uint32_t * data;
  // lenght (in bits) of the vector
  int        number_of_bits;
} ;

// typedef ==> make an alias for "struct _bitvec"
typedef struct _bitvec BitVec;
#else
typedef struct {
  // pointer to a vector of integer which store the bits
  uint32_t * data;
  // lenght (in bits) of the vector
  int        number_of_bits;
  int        number_of_uint32_t;
} BitVec;
#endif

// prototypes of functions for BitVec manipulations

// allocate data for nbits
void BitVec_new( BitVec * bv, int nbits );

// destroy the BitVec (free allocated memory)
void BitVec_delete( BitVec * bv );

// initialize a BitVec to all bits  zeros
void BitVec_allzero( BitVec * bv );
void BitVec_allone( BitVec * bv );

void BitVec_off( BitVec * bv, int which_bit );
void BitVec_on( BitVec * bv, int which_bit );
int  BitVec_get( BitVec * bv, int which_bit );
void BitVec_negate( BitVec * bv, int which_bit );

#endif
