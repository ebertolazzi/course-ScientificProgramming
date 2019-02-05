#include <stdio.h>
#include <stdlib.h>

/*
 * Pointer arithmetic
 *
 */

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

  float  *p1, *p2, *p3 ; /* define 3 pointers to float */

  printf("sizeof(float*) = %lu\n",sizeof(float*));

  p1 = a ; /* p1 ora punta al primo elemento */
  /*            +------+
   * p1 = a --> |  1.0 |
   *            +------+
   *            |  2.0 |
   *            +------+
   *            | -1.0 |
   *            +------+
   *            | -2.0 |
   *            +------+
   *            | 3.4  |
   *            +------+
   *            | 5.0  |
   *            +------+
   *            | -7.0 |
   *            +------+
   *            | 0.0  |
   *            +------+
   */
  printf("Primo elemento a[0] = %g *p1 = %g\n", a[0], *p1) ;
  printf("Indirizzo elemento &a[0] = %X p1 = %X\n",
         (unsigned)(&a[0]),
         (unsigned)(p1)) ;
  
  p2 = a+3 ; /* p2 ora punta al quarto elemento */
  /*            +------+
   * p1 = a --> |  1.0 |
   *            +------+
   *            |  2.0 |
   *            +------+
   *            | -1.0 |
   *            +------+
   *     p2 --> | -2.0 |
   *            +------+
   *            | 3.4  |
   *            +------+
   *            | 5.0  |
   *            +------+
   *            | -7.0 |
   *            +------+
   *            | 0.0  |
   *            +------+
   */
  printf("Primo elemento a[3] = %g *p2 = %g\n", a[3], *p2) ;
  printf("Indirizzo elemento &a[3] = %X p2 = %X\n",
         (unsigned)(&a[3]),
         (unsigned)(p2)) ;

  p3 = p2+2 ; /* p3 ora punta al sesto elemento */
  /*            +------+
   * p1 = a --> |  1.0 |
   *            +------+
   *            |  2.0 |
   *            +------+
   *            | -1.0 |
   *            +------+
   *     p2 --> | -2.0 |
   *            +------+
   *            | 3.4  |
   *            +------+
   *     p3 --> | 5.0  |
   *            +------+
   *            | -7.0 |
   *            +------+
   *            | 0.0  |
   *            +------+
   */
  printf("Primo elemento a[5] = %g *p3 = %g\n", a[5], *p3) ;
  printf("Indirizzo elemento &a[5] = %X p3 = %X\n",
         (unsigned)(&a[5]),
         (unsigned)(p3)) ;

  /* posso fare la differenza tra puntatori.
     In risultato e' un intero (con segno) e
     rappresenta la differenza in celle 
     della dimensione del tipo puntato */

  printf("p2-p3= %ld\n",p2-p3) ;
  printf("reinterpretati come puntatori a char p2-p3= %ld\n",
        (char*)p2-(char*)p3) ;
  printf("reinterpretati come puntatori a double p2-p3= %ld\n",
        (double*)p2-(double*)p3) ;

  /* 
   * facciamo arrabbiare il sistema operativo
   *
   */

  printf("*p3= %g\n",*p3) ;
  p3 = (float*)((char*)p2-1) ; 
      /*  |        |
       *  |        +-- decremento il puntatore come
       *  |            puntatore a carattere, quindi p3
       *  |            non puntera a inizio "parola".
       *  +--- reinterpreto l'indirizzo come puntatore a float
       *       mi aspetto un errore di accesso alla memoria in
       *       fase di esecuzione, o un valore floating point
       *       sensa senso
       */
  printf("*p3= %g\n",*p3) ;
  p3 = (float*)((char*)p2-4) ; 
  printf("*p3= %g\n",*p3) ;

  return 0 ;
}
