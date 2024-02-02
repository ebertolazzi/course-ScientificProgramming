/*\

  implementation of power

\*/

#include "power.h"

int mult_count;

double
power1( double a, int b ) {
  double res = 1;
  for ( int i=0; i < b; ++i ) { res *= a; ++mult_count; }
  return res;
}


double
power2( double a, int b ) {
  double res  = 1;
  int    absb = b > 0 ? b : -b; 
  for ( int i=0; i < absb; ++i ) { res *= a; ++mult_count; }
  if ( b < 0 ) { res = 1/res; ++mult_count; }
  return res;
}

double
power3( double a, int b ) {
  // optimized version of power
  int    absb = b > 0 ? b : -b;
  double res  = (absb&0x01) != 0 ? a : 1;
  double a2n  = a;
  // b = b0*2^0 + b1*2^1 + ... + bn * 2^n
  // a^b = a^(b0*2^0 + b1*2^1 + ... + bn * 2^n)
  //     = a^(b0*2^0) * a^(b1*2^1) * .. * a^(bn * 2^n)
  //     = a^(b0) * (a^2)^(b1) * .. * (a^(2^n))^(bn)
  // we need 
  //     a, a^2, a^4, a^8, a^16
  while ( absb > 0 ) {
    // update the power a^(2^k)
    // various way to compute a^(2^k)
    // a2n = a2n*a2n;
    a2n *= a2n; //a, a^2, a^4, a^8
    ++mult_count;
    // various way to divide by 2
    // absb = absb/2;
    // absb /=2;
    // absb = absb>>1;
    absb >>= 1;
    // if bk != 0, then a^(bk*2^k) must be accumulated
    if ( (absb&0x01) != 0 ) { res *= a2n; ++mult_count; }
  }
  // check if b < 0 --> reverse the power
  if ( b < 0 ) { res = 1/res; ++mult_count; }
  return res;
}