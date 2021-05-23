/*
   Example to print first 100 numbers,
   10 by line.
 */

// include definition for printf, scanf...
#include <stdio.h>
 
int
main ()
{
  int i; // declare i as an integer variable

  /*\
    for ( INIT; CHECK; INCREMENT ) ISTRUCTION;
  \*/

  for ( i = 1   ; // initializing block (execute 1 time at the beginnig) 
        i < 100 ; // expression that evaluate to a boolean,
                  // executed ad the beginning of a cicle
                  // the cicle interrupt when evaluate to false
                  // comparison operators:
                  //  a <  b : a less than b
                  //  a <= b : a less than or equal to b
                  //  a >  b : a greater than b
                  //  a >= b : a greater than or equal to b
                  //  a == b : a equal to b
                  //  a != b : a not equal to b
        ++i )     // block executed at the end of each cicle
                  // ++ is the increment operator, equivalent i = i+1
  { // block of istruction executed at each cicle
    
    // two different print depending if i is divisible by 10
    // a % b  = remainder of a/b i.e a = b*k+ r where a, b, k, r are integer
    // a == b = return true if a is equal to b
    // a || b = logical "or" true if a or b evaluate to true
    // a && b = logial "and" true if both a and b evaluate to true
    if ( (i % 10) == 0 || i == 99 ) {
      printf("%-5d\n", i) ;
    } else {
      printf("%-5d,", i) ;
    }
  }

  return 0 ;
} // closing brace is the end of the program
