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
compare_double( void const * pa, void const * pb) {
  /* * (aterisco) e' un operatore di deferenziazione
     cioe' vado alla locazione indicata dal puntatore
     ed estraggo il contenuto */
  double a = * (double*) pa ;
  /*     ^   ^     ^      ^
   *     |   |     |      |
   *     |   |     |      +--- puntatore all'elemento
   *     |   |     +--- operatore di "CAST" cioe' reinterpreta
   *     |   |          quello che sta alla sua destra nel tipo
   *     |   |          indicato in parentesi.
   *     |   |          In questo caso, "pa" passa da puntatore 
   *     |   |          a void a puntatore a double
   *     |   |
   *     |   +--- * (asterisco) e' l'operatore di deferenziazione
   *     |          cioe' prende il contenuto della zona di memoria
   *     |          indirizzata dal puntatore.
   *     |
   *     +-- variabile che memorizzera una copia
   *         del "doble" puntato da pa
   */

  double b = * (double*) pb ;

  if ( a < b ) return -1 ;
  if ( a > b ) return +1 ;
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

  qsort( a, size, sizeof(a[0]),
         compare_double /* compare_double e' un puntatore a funzione */
       ) ;

  printf("Vettore ordinato: %lg",a[0]);
  for ( i=1; i < size ; ++i )
    printf( ", %lg",a[i]) ;
  printf("\n");
 
  return 0 ;
}
