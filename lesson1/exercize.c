#include <stdio.h>

/*\
 *  Write a program that compute 3-bonacci number
 *
 *  F(n) = n th number of 3-Bonacci
 *
 *  F(0) = 1
 *  F(1) = 1
 *  F(2) = 1
 *  F(n+1) = F(n) + F(n-1) + F(n-2) n = 2,3,...
 *
 *
 *  1,1,1,3,5,9,....
 *
\*/

unsigned long
threeBonacci( unsigned long n ) {
  unsigned long tbn;
  // do something


  return tbn;
}

int
main() {
  unsigned long n, tbn;

  printf("Give me a number: " ) ;

  scanf("%XXX",&n);

  // print some messages...

  // call the function
  tbn = threeBonacci( n );

  printf("F(%XXX) = %XXX\n", n, tbn);

  return 0 ;
}
