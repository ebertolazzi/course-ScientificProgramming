#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Aritmetica dei puntatori
 *
 * allocazione dinamica della memoria.
 *
 */

/*
 * Esercizio stupido.
 *
 * Dati due vettori a e b costruisco la matrice
 * M = I + a b^T
 *
 *     +---------+
 * a = | a[0]    |
 *     +---------+
 *       ....
 *     +---------+
 *     | a[n-1]  |
 *     +---------+
 *
 *     +---------+
 * b = | b[0]    |
 *     +---------+
 *       ....
 *     +---------+
 *     | b[n-1]  |
 *     +---------+
 *
 *  AD ESEMPIO
 *                    +       +   +   + +       +
 *                    | 1     |   | 1 | | 2 3 3 |
 *  M = I + a b^T =   |   1   | + | 2 | +       +
 *                    |     1 |   | 1 |
 *                    +       +   +   +
 *      +       +
 *      | 3 3 3 |
 *    = | 4 7 6 |
 *      | 2 3 4 |
 *      +       +
 *
 * Una volta costruita M calcolo la norma-1
 *
 *              n   n
 * || M ||_1 = max sum | Mij |
 *             J=1 i=1
 *
 *  Uso per macro per usare gli indici a partire a 1.
 *
 */

double /* norma risultante */
norma1_di_un_vettore( double const a[],
                      int    const n ) {
  int    i ;
  double res = 0 ;
  for ( i = 0 ; i < n ; ++i )
    res += fabsf(a[i]) ;
  return res ;
}

double /* norma risultante */
routine_inutile( double const a[],
                 double const b[],
                 int    const n ) {
   /* uso la allocazione dinamica per questioni 
      didattiche.
      Esercizio, riscrivere la routione SENZA
      allocazione dinamica */
   double * M ; /* puntatore alla matrice da allocare */
   double * p ; /* puntatore genrico per fare conti */
   double res ; /* memorizzo la norma 1 della matrice */
   double tmp ;
   int i,j ;    /* interi generici per i cicli vari */
  
   /* allocazione dinamica */
   M = malloc( n*n*sizeof(double)) ;

   /* Da aggiungere il controllo della allocazione dinamica */

   /*
    * Per la matrice M puo essere memorizzata 
    * per "colonne", cioe'
    * M(riga,colonna) = M[riga-1+(colonna-1)*n]
    * per "righe", cioe'
    * M(riga,colonna) = M[colonna-1+(riga-1)*n]
    *
    */
  
  /* uso la macro per "risparmiare" le dita
     uso la allocazione per colonne */
  #define M(I,J) M[(I-1)+(J-1)*n] 
  /* NOTA: cosa fa la macro ?
   *
   * se ad esempio scrivo
   *   M(i,j+1) questo viene espanso in 
   *   M[(i-1)+(j+1-1)*n].
   * ovviamente la macro e' piu' leggibile
   * ma bisogna definirne una per ogni matrice
   */

  #define a(I) a[I-1] 
  #define b(I) b[I-1] 
  /* per evitare di scrivere a[i-1] b[j-1]
     uso la macro per scrivere a(i) e b(i) */
  /* passo 1 setto M(i,j) = a(i)*b(j) */
  for ( i = 1 ; i <= n ; ++i )
    for ( j = 1 ; j <= n ; ++j )
      M(i,j) = a(i)*b(j) ;

  /* se non avessi usato le macro
     l'istruzione diventava:
     M(i,j) = a(i)*b(j) ===> M[i-1+(j-1)*n] = a[i-1]*b[j+1]

     oppure cambiando i cicli ad iniziale da 0
     for ( i = 0 ; i < n ; ++i )
       for ( j = 0 ; j < n ; ++j )
         M[i+j*n] = a[i]*b[j] ;
  */

  /* aggiungo la matrice identita' */
  for ( i = 1 ; i <= n ; ++i )
    M(i,i) += 1 ; /* e' equivalente a M(i,i) = M(i,i) + 1 ; */

  /* calcolo della norma 1 */
  res = 0 ;
  for ( i = 1 ; i <= n ; ++i ) {
    p   = & M(1,i) ; /* Puntatore alla i-esima colonna */
    tmp = norma1_di_un_vettore( p, n ) ;
	if ( tmp > res ) res = tmp ;
  }
 
  /* libero la memoria utilizzata */
  free( M ) ;

  return res ; /* norma 1 di M */
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
  int    size = sizeof(a)/sizeof(a[0]) ;
  double res ;
  
  res = routine_inutile( a, a, size ) ;

  printf("Risultato = %lg\n",res ) ;

  return 0 ;
}
