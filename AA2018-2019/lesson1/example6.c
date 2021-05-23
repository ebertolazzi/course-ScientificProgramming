#include <stdio.h> /* da spiegare piu' avanti */

/*
 * in C there exists predefined "types"
 *
 * int = ineger with sign, typical size is
 *       2, 4 or 8 bytes.
 *
 * float  = floating point number singple precision (4 bytes)
 *
 * double = floating point number double precision (8 bytes)
 *
 * char = charater type, 1 byte used for ascii character
 *
 */

/*
 * Some "modifier"
 *
 * unsigned = in front of `int` and `char`.
 *            unsigned int
 *            unsigned char.
 *            You can use the shortcut
 *            unsigned = unsigned int
 *
 * signed = in front of `int` and `char`.
 *            signed int
 *            signed char.
 *            You can use the shortcut
 *            int = signed int
 *            signed char != unsigned char
 *
 * short = in front of `int`
 *         You can use the shortcut
 *         short = short int
 *
 * long = in front of `int`
 *        You can use the shortcut
 *        long = long int *
 */

int
main()
{
  /*
   * some example
   */

  int i, j, k; /* define i,j,k as integer with sign */

  short l, m;  /* define l,m as signed short integer */
 
  float a, b; /* define a,b as floating point
                 singola precision */

  double c, d; /* define c,d as floating point
                  double precision*/

  unsigned int o, p; /* define o, p
                        as integer without sign */

  unsigned long int r, s; /* define o, p
                             as big integer without sign */

  /*
   * sizeof(argument) : argument is a type or a variable
   *                    return the number of bytes
   *                    used to store it
   *
   */

  printf("n. byte used for \"char\" %ld\n", sizeof(char)) ;
  printf("n. byte used for \"short\" %ld\n", sizeof(short)) ;
  printf("n. byte used for \"int\" %ld\n", sizeof(int)) ;
  printf("n. byte used for \"long\" %ld\n", sizeof(long)) ;
  printf("n. byte used for \"float\" %ld\n", sizeof(float)) ;
  printf("n. byte used for \"double\" %ld\n", sizeof(double)) ;
  

  i = 11 ;
  j = 23 ; k = 3434 ;

  printf("numer in decimal i=%d j=%10d k=%-10d***\n",i,j,k) ;

  printf("numer in octal i=%o j=%10o k=%-10o***\n",i,j,k) ;

  printf("numer in hexadecimal i=%x j=%10x k=%-10X***\n",i,j,k) ;
 
  /*
  // Formatting
  //
  // %d    integer decimal
  // %ld   integer long decimal
  // %o    integer in octal
  // %x %X integer in hexadecimal
  //
  // %23d  reserve 23 spaces for the print
  //       with right alignment
  // %-12d reserve 12 spaces for the print
  //       with left alignment
  */

  l = m = -12 ; /* equivalent to write
                  m = 12 ; l = m ; */

  printf("number (short) l=%d m=%10d\n",l,m) ;

  a = b = 1.2f ; /* f e' postfisso per indicare
                    la singola precisione */

  printf("number (float) a[%%f]=%f b[%%10f]=%10f\n",a,b) ;
  printf("number (float) a[%%10.2f]=%10.2f b[%%-10.4f]=%-10.4f\n",a,b) ;
  
  c = 1.2 ;
  d = 2 ;

  printf("number (double) c[%%lf]=%lf d[%%10lf]=%10lf\n",c,d) ;
  printf("number (double) c[%%10.2lf]=%10.2lf d[%%-10.4lf]=%-10.4lf\n",c,d) ;

  /*
  // Formatting floating point numbers
  //
  // %f      singola precision
  // %lf     double precision
  // %10f    riserve 10 spaces for the print
  // %10.4f  riserve 10 spaces for the print, 4 for the decimal part
  // %-10f   riserve 10 spaces for the print left aligned
  //
  // instead of "f" use "e" for esponential format
  // 12.34 ==> 1.234E1 E1 = 10^1
  //
  // instead of "f" use "g" for esponential format
  // when convenient
  //
  */
  printf("number (double) c[%%lg]=%lg d[%%10lg]=%10lg\n",c,d) ;
  printf("number (double) c[%%10.2le]=%10.2le d[%%-10.4le]=%-10.4le\n",c,d) ;

  o = -1 ; /* warning! assign signed integr to unsigned */
  p = 2  ;

  r = s = 12 ;

  return 0 ;
}
