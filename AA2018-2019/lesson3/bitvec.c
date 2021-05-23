#include "bitvec.h"

#include <stdio.h> // for calloc and free
#include <stdlib.h> // for calloc and free

// prototypes of functions for BitVec manipulations

// allocate data for nbits
void
BitVec_new( BitVec * bv, int nbits ) {
  // count the number of uint32_t that are needed

  // plain computation
  //n = nbits / 32;
  //if ( (nbits % 32) != 0 ) ++n;

  // erudite computation
  bv -> number_of_uint32_t = (nbits>>5) + ( (nbits & 0x1F) != 0 ? 1 : 0 );

  bv -> data = calloc( bv -> number_of_uint32_t, sizeof(uint32_t) );

  // check allocation
  if ( bv -> data == NULL ) {
    printf("Allocation of %d uint32_t failed:",
           bv -> number_of_uint32_t );
    exit(0);
  } else {
    printf("Allocated %d uint32_t.\n",
           bv -> number_of_uint32_t );
  }

  bv -> number_of_bits = nbits;
}

// destroy the BitVec (free allocated memory)
void
BitVec_delete( BitVec * bv ) {
  if ( bv -> data != NULL ) {
    free( bv -> data );
    bv -> data = NULL;
  }
  bv -> number_of_bits     = 0;
  bv -> number_of_uint32_t = 0;
}

// initialize a BitVec to all bits  zeros
void
BitVec_allzero( BitVec * bv ) {
  int i;
  for ( i = 0; i < bv -> number_of_uint32_t; ++i )
    bv -> data[i] = 0;
}

void
BitVec_allone( BitVec * bv ) {
  int i;
  uint32_t ones = 0; ones = ~ones;
  for ( i = 0; i < bv -> number_of_uint32_t; ++i )
    bv -> data[i] = ones;
}

void
BitVec_off( BitVec * bv, int which_bit ) {
  // search the position
  int ipos = which_bit>>5;   // which_bit/32
  int ibit = which_bit&0x1F; // which_bit%32
  uint32_t bit = 1<<ibit;
  // bv->data[ipos] = bv->data[ipos] & ~bit;
  bv->data[ipos] &= ~bit;
  // A = A OP B --> A OP= B
  // OP = + - * / & ^ |
}

void BitVec_on( BitVec * bv, int which_bit ) {
  // search the position
  int ipos = which_bit>>5;   // which_bit/32
  int ibit = which_bit&0x1F; // which_bit%32
  uint32_t bit = 1<<ibit;
  // bv->data[ipos] = bv->data[ipos] & ~bit;
  bv->data[ipos] |= bit;
}

int  BitVec_get( BitVec * bv, int which_bit ) {
  // search the position
  int ipos = which_bit>>5;   // which_bit/32
  int ibit = which_bit&0x1F; // which_bit%32
  uint32_t bit = 1<<ibit;
  // ( IF ? TRUE : FALSE ) ;
  return ( (bv->data[ipos]&bit) != 0 ? 1 : 0 ) ;
}

void
BitVec_negate( BitVec * bv, int which_bit ) {
  // search the position
  int ipos = which_bit>>5;   // which_bit/32
  int ibit = which_bit&0x1F; // which_bit%32
  uint32_t bit = 1<<ibit;
  // bv->data[ipos] = bv->data[ipos] & ~bit;
  bv->data[ipos] ^= bit; // xor with 1
}
