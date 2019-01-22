#include <stdio.h> /* da spiegare piu' avanti */

/*
 * in C esistono un certo numeri di "tipi"
 * numerici predefiniti:
 *
 * int = intero con segno, tipicamente composto
 *       da 2 o 4 o 8 byte. Il numero di byte e'
 *       quello della "parola" (word) del processore.
 *       Ad esempio su processori a 32 bit (4 byte)
 *       l'intero e' di 4 byte.
 *
 * float  = numero floating point in singola precisione
 *          tipicamante 4 byte
 *
 * double = numero floating point in doppia precisione
 *          tipicamante 8 byte
 *
 * char = tipo carattere, un byte usato per memorizzare
 *        un carattere (ascii)
 *
 */

/*
 * A questi tipi si possono mettere dei "modificatori"
 *
 *
 * unsigned = si applica a int e char.
 *            l'intero e il carattere non hanno segno
 *            unsigned int
 *            unsigned char.
 *            Di solito si usa la forma abbreviata
 *            unsigned = unsigned int
 *
 * short    = si applica a int
 *            short int e' un intero che puo' usare
 *            meno byte di int, tipicamente 2 byte
 *            su un processore a 32 bit.
 *            Di solito si usa la forma abbreviata
 *            short = short int
 *
 * long     = si applica a int e double
 *            long int e' un intero che puo' usare
 *            piu' byte di int, tipicamente 8 byte
 *            su un processore a 32 bit.
 *            long double e' una numero floating
 *            point di precisione quadrupla.
 *            Non e' implementato su tutti i compilatori.
 *
 */

int
main()
{
  /*
   * alcuni esmopi d'uso
   */

  int i, j, k; /* definisco le variabili i,j,k
                  come varibili intere con segno */

  short l, m;  /* definisco le variabili l,m
                  come varibili intere "corte" con segno */
 
  float a, b; /* definisco le variabili a,b
                 come varibili floating point
                 in singola precisione */

  double c, d; /* definisco le variabili c, d
                   come varibili floating point
                   in doppia precisione */

  unsigned int o, p; /* definisco le variabili o, p
                        come varibili intere
                        senza segno */

  unsigned long int r, s; /* definisco le variabili r, s
                             come varibili intere
                             senza segno "lunghe" */

  /*
   * sizeof(argument) : argument e' un tipo
   *                    restituisce il numero di byte
   *                    usato per rappresentarlo 
   *
   */

  printf("n. byte per tipo \"char\" %ld\n", sizeof(char)) ;
  printf("n. byte per tipo \"short\" %ld\n", sizeof(short)) ;
  printf("n. byte per tipo \"int\" %ld\n", sizeof(int)) ;
  printf("n. byte per tipo \"long\" %ld\n", sizeof(long)) ;
  printf("n. byte per tipo \"float\" %ld\n", sizeof(float)) ;
  printf("n. byte per tipo \"double\" %ld\n", sizeof(double)) ;
  

  /* assegnazioni varie */
  i = 11 ;
  j = 23 ; k = 3434 ; /* posso scrivere piu'
                     instruzioni per riga */

  printf("numeri in decimale i=%d j=%10d k=%-10d***\n",i,j,k) ;

  /* stampo i numeri in ottale */
  printf("numeri in ottale i=%o j=%10o k=%-10o***\n",i,j,k) ;

  /* stampo i numeri in esadecimale */
  printf("numeri in esadecimale i=%x j=%10x k=%-10X***\n",i,j,k) ;
 
  /*
  // Formattazione stampa interi
  //
  // %d    intero decimale
  // %ld   intero long decimale
  // %o    intero in ottale
  // %x %X intero in esadecimale
  //
  // %23d  riservo 23 spazi per la stampa
  //       con allineamento a a destra
  // %-12d riservo 12 spazi per la stampa
  //       con allineamento a sinistra
  */

  l = m = -12 ; /* equivalente a scrivere 
                  m = 12 ; l = m ; */

  printf("numeri (short) l=%d m=%10d\n",l,m) ;

  a = b = 1.2f ; /* f e' postfisso per indicare
                    la singola precisione */

  printf("numeri (float) a[%%f]=%f b[%%10f]=%10f\n",a,b) ;
  printf("numeri (float) a[%%10.2f]=%10.2f b[%%-10.4f]=%-10.4f\n",a,b) ;
  
  c = 1.2 ;
  d = 2 ;

  printf("numeri (double) c[%%lf]=%lf d[%%10lf]=%10lf\n",c,d) ;
  printf("numeri (double) c[%%10.2lf]=%10.2lf d[%%-10.4lf]=%-10.4lf\n",c,d) ;

  /*
  // Formattazione stampa numeri in floating point
  //
  // %f      singola precisione
  // %lf     doppia precisione
  // %10f    riservo 10 spazi per la stampa
  // %10.4f  riservo 10 spazi per la stampa, 4 per la parte decimale
  // %-10f   riservo 10 spazi per la stampa allineato a sinista
  //
  // al posto di "f" posso usare "e" per formato esponenziale
  // 12.34 ==> 1.234E1 E1 = 10^1
  //
  // al posto di "f" posso usare "g" per formato esponenziale
  // quando conviene
  //
  */
  printf("numeri (double) c[%%lg]=%lg d[%%10lg]=%10lg\n",c,d) ;
  printf("numeri (double) c[%%10.2le]=%10.2le d[%%-10.4le]=%-10.4le\n",c,d) ;

  o = -1 ; /* occhio! assegno intero con segno ad un unsigned */
  p = 2  ;

  r = s = 12 ;

  return 0 ;
}
