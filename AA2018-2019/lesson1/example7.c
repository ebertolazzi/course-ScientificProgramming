#include <stdio.h>


/*
 *  esempio programma che calcola n esimo 
 *  numero di Fibonacci.
 *
 *  F(n) = n esimo numero di Finonacci
 *
 *  F(0) = 1
 *  F(1) = 1
 *  F(n+1) = F(n) + F(n-1) n =1,2,3,... 
 *
 *
 *  1,1,2,3,5,8,....
 *
 */


int
main()
{

  int fk, fkp1, fkm1, k, n ; /* variabili usate dall'algoritmo */

  /* stampa sul terminale il messaggio
     che richiede il rangop del numero da calcolare */

  printf("Calcolo del n-esimo numero di Fibonacci\n" /* stringa su piu' righe */
         "inserisci n: " ) ;

  /* lettura da terminale del numero n */
  scanf("%d",&n) ; /* & estrae l'indirizzo della variabile n */

  printf("Hai inserito il numero n = %d\n", n) ;

  /*
   * if ( espressione logica ) istruzione ;
   *
   * istruzione puo' essere anche un blocco di istruzioni
   * racchiuse da { }
   *
   */

  if ( n == 0 ) {
    printf("F(0) = 1\n") ; /* stampo il risultato */
    return 0 ; /* esco dal programma "bene" */
  }

  if ( n == 1 ) {
    printf("F(1) = 1\n") ; /* stampo il risultato */
    return 0 ; /* esco dal programma "bene" */
  }

  fkm1 = fk = 1 ; /* parto con k = 1 */
  k    = 1 ;      /* intero per il ciclo */

loop_label: /* etichetta per fare dei goto */
  
  fkp1 = fk + fkm1;
  k    = k + 1;  // you can use ++k or k++
  /* shift degli elementi */
  fkm1 = fk;
  fk   = fkp1;

  /* controllo se ho finito il ciclo */
  if ( k != n ) goto loop_label;
    /* instruzione goto "salta" alla etichetta "loop_label".
     * Etichetta e' una qualunue sequenza alfanumerica (senza spazi)
     *
     */

  printf("F(%d) = %d\n", n, fk) ; /* stampo il risultato */

  return 0 ;
}
