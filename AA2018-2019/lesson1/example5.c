
#include <stdio.h>

void // do not return anything
example(
  int    * p_a, // arguments of the function passed by addess
  int    * p_b,
  int    * p_c,
  float  * p_aa,
  double * p_bb
) {
  printf("I am a string\n") ;

  // now assign the variable a, b, c to some value
  // *p_a "deference" the variable at the addess p_a
  *p_a = 1;
  *p_b = 234;
  *p_c = -123;

  printf("Write a formatted integer a = %i\n",*p_a) ;
  printf("Write a formatted integer a = %10i, b=%5i\n",*p_a,*p_b) ;
  printf("Write a formatted integer a = %-10i, b=%5i, c=%6i\n",*p_a,*p_b,*p_c) ;

  *p_aa = 1.234; // declare, instance and initialize aa as floating point variable
  printf("Write aa formatted aa = %f\n",*p_aa) ;
  printf("Write aa formatted aa = %10f\n",*p_aa) ;
  printf("Write aa formatted aa = %10.5f\n",*p_aa) ;
  printf("Write aa formatted aa = %e\n",*p_aa) ;
  printf("Write aa formatted aa = %10g\n",*p_aa) ;

  *p_bb = 13.234; // declare, instance and initialize aa as floating point variable
  printf("Write bb formatted bb = %f\n",*p_bb) ;
  printf("Write bb formatted bb = %10f\n",*p_bb) ;
  printf("Write bb formatted bb = %10.5f\n",*p_bb) ;
  printf("Write bb formatted bb = %e\n",*p_bb) ;
  printf("Write bb formatted bb = %10g\n",*p_bb) ;
}

int
main( /* no argument for the moment */ ) {
  int    a, b, c; // declare and instance a,b,c as integer variable
  float  aa;
  double bb, cc;
  printf("I am a string\n") ;
  
  // now assign the variable a, b, c to some value
  a = 1;
  b = 234;
  c = -123;
  aa = 1.234; // declare, instance and initialize aa as floating point variable
  bb = 13.234; // declare, instance and initialize aa as floating point variable
  // & get the addess of the variables
  example( &a, &b, &c, &aa, &bb );

  return 0 ; // return 0 to the OS
}
