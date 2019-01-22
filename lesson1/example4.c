
#include <stdio.h>

void // do not return anything
example(
  int    a, // arguments of the function
  int    b,
  int    c,
  float  aa,
  double bb
) {
  printf("I am a string\n") ;

  // now assign the variable a, b, c to some value
  a = 1;
  b = 234;
  c = -123;

  printf("Write a formatted integer a = %i\n",a) ;
  printf("Write a formatted integer a = %10i, b=%5i\n",a,b) ;
  printf("Write a formatted integer a = %-10i, b=%5i, c=%6i\n",a,b,c) ;

  aa = 1.234; // declare, instance and initialize aa as floating point variable
  printf("Write aa formatted aa = %f\n",aa) ;
  printf("Write aa formatted aa = %10f\n",aa) ;
  printf("Write aa formatted aa = %10.5f\n",aa) ;
  printf("Write aa formatted aa = %e\n",aa) ;
  printf("Write aa formatted aa = %10g\n",aa) ;

  bb = 13.234; // declare, instance and initialize aa as floating point variable
  printf("Write bb formatted bb = %f\n",bb) ;
  printf("Write bb formatted bb = %10f\n",bb) ;
  printf("Write bb formatted bb = %10.5f\n",bb) ;
  printf("Write bb formatted bb = %e\n",bb) ;
  printf("Write bb formatted bb = %10g\n",bb) ;
}

int
main( /* no argument for the moment */ ) {
  int    a, b, c; // declare and instance a,b,c as integer variable
  float  aa;
  double bb;
  printf("I am a string\n") ;
  
  // now assign the variable a, b, c to some value
  a = 1;
  b = 234;
  c = -123;
  aa = 1.234; // declare, instance and initialize aa as floating point variable
  bb = 13.234; // declare, instance and initialize aa as floating point variable
  example( a, b, c, aa, bb );

  return 0 ; // return 0 to the OS
}
