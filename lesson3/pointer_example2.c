#include <stdio.h>
#include <stdlib.h>

/*
 * Aritmetica dei puntatori
 *
 * loop su vettore
 */

void
stampa_vec( float const a[], int const dima) {
  int i ;
  printf("%g",a[0]);
  for ( i=1; i < dima ; ++i )
    printf( ", %g",a[i]) ;
  printf("\n");
}

int
main() {

  float a[] = {1, 2, -1, -2, 3.4, 5,-7, 0 };

  /*       +------+
   * a --> |  1.0 |
   *       +------+
   *       |  2.0 |
   *       +------+
   *       | -1.0 |
   *       +------+
   *       | -2.0 |
   *       +------+
   *       | 3.4  |
   *       +------+
   *       | 5.0  |
   *       +------+
   *       | -7.0 |
   *       +------+
   *       | 0.0  |
   *       +------+
   */

  int const dima = sizeof(a)/sizeof(a[0]) ;
    /* memorizzo la dimensione di a su una costante */

  float *pa, *pb ; /* definisco 2 puntatori a float */
  float b[dima-1] ; /* dimensione di a - 1 */
  int i ;
  /* voglio costruire il vettore b che contiene
   * all'i-esima posizione
   *
   * b[i] = a[i+1]-a[i]
   *
   */

  /* modo triviale */
  for ( i=0 ; i < dima -1 ; ++i ) b[i] = a[i+1]-a[i] ;
  printf("Differenza modo 1\n") ;
  stampa_vec( a, dima ) ;

  /* usando i puntatori */
  for ( pa = a, pb = b ; pa < a + dima - 1 ; ++pa, ++pb )
    *pb = pa[1]-pa[0] ;
  /*   *pa     e' equivalente a pa[0]
   *   *(pa+1) e' equivalente a pa[1]
   *
   *   occhio che a e b pur essendo puntatori non 
   *   sono modificabili, cioe' non posso scivere ++a
   *   o b = b -1  etc etc
   */

  printf("Differenza modo 2\n") ;
  stampa_vec( a, dima ) ;


  return 0 ;
}
