#include <stdio.h>
#include <stdlib.h>

/*
 * Vettori e Matrici:
 *
 * ordinamento quick sort usando routione 
 * di sistema (libreria C standard)
 *
 */

/*
 * routine di confronto di due numeri 
 * in doppia precisione
 *
 * la funzione deve essere del tipo:
 * int (*compar)(const void *, const void *)
 */

/*
 * void const * pa ; 
 * con questa dichiarazione pa e' un puntatore
 * a senza tipo a della memoria non modifcabile
 */

int
compare_double( double const * pa, double const * pb) {

  /* *pa e' il valore del numero "double" puntato da pa */
  /* *pb e' il valore del numero "double" puntato da pb */

  if ( *pa < *pb ) return -1 ;
  if ( *pa > *pb ) return +1 ;
  return 0 ;
}


int
main() {
  /* dichiarazione con inizializzazione */
  double a[] = { 2, 3, -1, 5, 6, 0, -3, -4 } ;
  /* in vettore verra' dimensionato al numero di elementi
     nella lista tra { }, in questo caso a 8 */
  /* si poteva anche scrivere
      int a[8] = { 2, 3, -1, 5, 6, 0, -3, -4 } ;
     ma se tolgo un elemento avrei un elemento 
     non inizializzato
   */
  int size = sizeof(a)/sizeof(a[0]) ;
  int i ;

  printf("Vettore non ordinato: %lg",a[0]);
  for ( i=1; i < size ; ++i )
    printf( ", %lg",a[i]) ;
  printf("\n");

  // PFUN e un "alias" del tipo funzione restituisce int 2 argoment puntatore a void
  typedef int (*PFUN) (const void *,const void *);

  qsort( a, size, sizeof(a[0]),
         (PFUN)compare_double /* compare_double e' un puntatore a funzione */
       ) ;

  printf("Vettore ordinato: %lg",a[0]);
  for ( i=1; i < size ; ++i )
    printf( ", %lg",a[i]) ;
  printf("\n");
 
  return 0 ;
}
