#include "power.hh"

// define the prototype of power
template <typename TYPE>
TYPE // generic type
power( TYPE a, int b ) {
  std::cerr << "Using " << typeid(TYPE).name() << '\n';
  // optimized version of power
  int absb = b > 0 ? b : -b;
  TYPE res = (absb&0x01) != 0 ? a : 1;
  TYPE a2n = a;
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
    // various way to divide by 2
    // absb = absb/2;
    // absb /=2;
    // absb = absb>>1;
    absb >>= 1;
    // if bk != 0, then a^(bk*2^k) must be accumulated
    if ( (absb&0x01) != 0 ) res *= a2n;
  }
  // check if b < 0 --> reverse the power
  if ( b < 0 ) res = 1/res;
  return res;
}

// ask the compiler to generate the code

template double power( double a, int b );
template float power( float a, int b );
template int power( int a, int b );
template long power( long a, int b );
