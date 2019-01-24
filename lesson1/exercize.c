#include <stdio.h>
#include <stdlib.h> // for exit()

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
threeBonacci_recursive(unsigned long n) {
  // close recursion
  if (n <= 2) return 1;

  return threeBonacci_recursive(n - 1) + threeBonacci_recursive(n - 2) +
         threeBonacci_recursive(n - 3);
}

unsigned long
threeBonacci(unsigned long n) {
  // close recursion
  if (n <= 2) return 1;
  unsigned long t3  = 1;
  unsigned long t2  = 1;
  unsigned long t1  = 1;
  unsigned long res = 1;
  int           j;
  for (j = 3; j <= n; ++j) {
    res = t1 + t2 + t3; // next 3-bonacci
    // check for overflow
    if (res <= t1) {
      printf("OVERFLOW!\n");
      exit(0);
    }
    // shift for next loop
    t3 = t2;
    t2 = t1;
    t1 = res;
  }
  return res;
}

int
main() {
  unsigned long n, tbn;

  printf("Give me a number: ");
  scanf("%lu", &n);

  // print some messages...

  // call the function
  tbn = threeBonacci(n);

  printf("F(%lu) = %lu\n", n, tbn);

  return 0;
}
