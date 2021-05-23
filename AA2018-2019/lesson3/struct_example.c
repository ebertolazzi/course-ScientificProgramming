/*
 * Programma inutile che esegue i seguenti compiti:
 *
 * Legge da un file un elenco di nomi+matricola+voto
 * riordina in vario modo (per nome, per voto per matricola)
 * salva le liste ordinate su altri file
 *
 */

#include <stdio.h>
#include <string.h> /* per la gestione delle stringhe e strerror */
#include <sys/errno.h> /* per leggere errno */
#include <stdlib.h> /* per la definizione di exit() */

/*
 * definisco la struttura che conterra' le informazioni
 * di una singola riga
 */

#define MAX_LEN       100
#define MATRICOLA_LEN 10

struct nome_della_struttura {
  char cognome[MAX_LEN] ;
  char nome[MAX_LEN] ;
  char matricola[MATRICOLA_LEN] ;
  int  voto ;
} ;

/*
 *  La struttura matricola verra' rappresentata in memoria
 *  in questo modo su una macchina a 32 bit
 *
 *        +---------------------------------+
 *        | cognome[0] ...  cognome[3]      | (singola parola di 32 bit/4 byte)
 *          .....
 *        | cognome[96]... cognome[99]      |
 *        +---------------------------------+
 *        | nome[0] ... nome[3]             | (singola parola di 32 bit/4 byte)
 *          .....
 *        | nome[96]... nome[99]            |
 *        +---------------------------------+
 *        | matricola[0] ... matricola[3]   |(singola parola di 32 bit/4 byte)
 *        | matricola[4] ... matricola[7]   |
 *        | matricola[8] matricola[9] 2 byte| // 2 bite di "padding" aggiunti
 *        +---------------------------------+
 *        | voto                            |
 *        +---------------------------------+
 *
 * cognome   usa 100 byte
 * nome      usa 100 byte
 * matricola usa 10  byte   
 * voto      usa 4   byte (su un processore a 32 bit)
 * ----------------------
 * totale        214 byte 214 / 4 = 53.25 (non divisibile x 4) 
 */

/*
 * definisco un vettore di 100 strutture
 */

struct nome_della_struttura a[100] ;

/*
 * typedef definisce dei sinonimi
 * in modo da accedere "senza" struct in fronte
 */

typedef struct nome_della_struttura tipo_struttura ;

/*
 * ora "tipo_struttura" e' un nuovo tipo come int double etc
 * e come tale lo possoo usare dichiarare nuove variabili etc.
 */

tipo_struttura b[100] ;


/*
 * subroutine di servizio per la stampa dei record
 */

static /* e' visibile solo in questo modulo */
void   /* non restituisce niente */
stampa_record( FILE * fd, /* descrittore file di uscita */
               tipo_struttura const record[],
               int const n_record ) {
  int i ;
  tipo_struttura const * ps ; /* puntatore ad un record */

  for ( i = 0 ; i < n_record ; ++i ) {
    ps = & record[i] ; /* modo 1: record[i] e' l'i-esimo record,
                                  con  & prendo il suo indirizzo */

    ps = record + i ; /* modo 2: sfrutto l'artimetica dei puntatori,
                                 record e' il puntatore al primo (0-esimo)
                                 elemento record + i e' l'indirizzo 
                                 dell'i-esimo record */
    fprintf(fd,
            "Record n. %d\n"
            "  Cognome:   %s\n"	
            "  Nome:      %s\n"	
            "  Matricola: %s\n"	
            "  Voto:      %d\n",
            i,
            (*ps) . cognome, /* modo 1: con * accedo al record e con ``.''
                                seleziono il campo della una struttura.
                                Non posso scrivere  perche'
                                l'operatore ``.'' ha precedenza piu' alta
                                dell'operatore ``*'' cioe'
                                *ps.cognome <--> *(ps.cognome)
                                e l'operatore ``.'' non e' definito sui
                                puntatori */
            ps -> nome,      /* modo 2: si usa l'operatore ``->'' come "alias"
                                di (* ). */
            ps -> matricola,
            ps -> voto) ;
  }
}

/*
 * FUNZIONE DI CONFRONTO RECORD per COGNOME
 */

int
compare_cognome(const void * _pa, const void * _pb) {
  tipo_struttura const * pa = (tipo_struttura const *) _pa ;
  tipo_struttura const * pb = (tipo_struttura const *) _pb ;
  return strcmp(pa -> cognome, pb -> cognome);
}

int
compare_matricola(const void * _pa, const void * _pb) {
  tipo_struttura const * pa = (tipo_struttura const *) _pa ;
  tipo_struttura const * pb = (tipo_struttura const *) _pb ;
  return strcmp(pa -> matricola, pb -> matricola);
}

int
compare_voto(const void * _pa, const void * _pb) {
  tipo_struttura const * pa = (tipo_struttura const *) _pa ;
  tipo_struttura const * pb = (tipo_struttura const *) _pb ;
  if ( pa -> voto == pb -> voto ) return 0 ;
  if ( pa -> voto >  pb -> voto ) return +1 ;
  else                            return -1 ;
}

int
main () {
  int            err_code ; /* usato per il codice di errore restituito dall I/O */
  char           nome_file[100] ;
  FILE *         descrittore_file ;
  int            n_record ;
  tipo_struttura record[1000] ; /* max 1000 nomi da ordinare */
   
  /*
   * FILE e' un tipo definito stdio.h che contiene
   * quello che serve per la gestione del file.
   */


  printf("NOME FILE ?:") ;
  scanf("%s",nome_file) ; /* %s e' il formato indicante una stringa
	                         non scrivo &nome_file perche nome_file e'
	                         gia un puntatore */

  printf("Apro il file: %s\n",nome_file) ;
  descrittore_file = fopen ( nome_file, "r" );

  /* controllo se l'apertura del file ha avuto successo */  
  if ( descrittore_file == NULL ) {
    perror("Ho trovato questo errore") ;
    printf("Stampo l'errore in modo alternativo\n" /* stringhe concatenate dal compilatore */
           "Cercando di aprire il file ``%s''\n"
           "ho trovato il seguente errore: ``%s''\n",
           nome_file, strerror(errno));
    /* 
     * PROBLEMA:
     * ho il testo in italiano e messaggi errore in inglese.
     * per scrivere un codice in multilingua occorre usare 
     * le opportunita di "locale.h" (vedi manuale libc)
     */
    exit(1) ; /* chiamata di sistema, uscita di brutto 
                 ripulisce un po tutto e chiude file eventualmente
                 aperti */
  }

  /*
   * apro il file 'nome_file' in lettura.
   *
   * i possibili modi di apertura di un file sono: 
   * ``r''   apro in lettura. Il puntatore e' posizionato sul primo carattere.
   * ``r+''  apro in lettura e scrittura. 
   *         Il puntatore e' posizionato sul primo carattere.
   * ``w''   Apre in scrittura un nuovo file. Se il file e' gia esistente
   *         lo cancella.
   * ``w+''  apro in lettura e scrittura. Se il file e' gia esistente
   *         lo cancella.
   * ``a''   Apre in scrittura un file.
   *         Se il file non esiste ne crea uno vuoto.
   *         Il puntatore e' posizionato sull'ultimo carattere.
   * ``a+''  Apre in lettura e scrittura un file.
   *         Se il file non esiste ne crea uno vuoto.
   *         Il puntatore e' posizionato sull'ultimo carattere.
   */

  /*
   * voglio saltare la prima riga che contine un commento
   */
  { /* apro nuovo blocco */
    int ch ; /* posso definire nuove variabili */
    while ( ( ch = fgetc(descrittore_file) ) != '\n' &&
              ch != EOF ) /* messuna istruzione */ ;
  }
  /* ch non e' piu' visibile */  

  for ( n_record = 0 ; /* inizializzo n_record */
        fscanf(descrittore_file, /* leggo dal file il cui descrittore e' descrittore_file */
               "%s%s%s%d",       /* cerco di convertire 3 stringhe e un intero */
               record[n_record].cognome,     /* per accedere ai campi di una struttura */
               record[n_record].nome,        /* si usa l'operatore ``.''               */
               record[n_record].matricola,   /* fscanf vuole i puntatori, quindi per le */
               & record[n_record].voto       /* stringhe non serve & */
               ) == 4 ; /* finche leggo 4 elementi continuo il ciclo */
        ++n_record ) {
    printf("Record n. %d\n"
           "  Cognome:   %s\n"	
           "  Nome:      %s\n"	
           "  Matricola: %s\n"	
           "  Voto:      %d\n",
           n_record,
           record[n_record].cognome,     /* per accedere ai campi di una struttura */
           record[n_record].nome,        /* si usa l'operatore ``.''               */
           record[n_record].matricola,
           record[n_record].voto) ;
  }

  /*
   * Ci sono 3 descrittori file associati a tre file standard
   * aperti in esecuzione del programma dal sistema operativo:
   *
   * FILE *stdin  -- stantard input  (lettura da terminale)  
   * FILE *stdout -- standard output (stampa su terminale)
   * FILE *stderr -- standard error  (stampa errori di solito su terminale)
   *
   * i descrittori sono riassegnabili, quindi posso cambiare
   * in esecuzione l'I/O su terminale e ridirigerlo su file o altro.
   * 
   * OCCHIO:
   * print(...) e' equivalente a fprintf(stdout,...)
   * scanf(...) e' equivalente a fscanf(stdin,...)
   */

  /* ordina i record per cognome */
  qsort( record,   /* puntatore inizio vettore da ordinare */
         n_record, /* intero con il numero di elementi da ordinare */
         sizeof(tipo_struttura), /* intero con il numero di byte occupato
                                    da un elemento del vettore */
         compare_cognome /* puntatore a fuzione di tipo
                          * int (*) (void const *,void const *)
                          * cioe' una funzione che dati due puntatori
                          * generici (che punteranno a due record del vettore da ordinare)
                          * restituisce un intero:
                          * 0   se li considero uguali
                          * > 0 se il primo elemeno puntato lo considero maggiore
                          *     del secondo elemento puntato.
                          * < 0 se il primo elemeno puntato lo considero minore
                          *     del secondo elemento puntato.
                          */
       ) ;
  printf("Lista ordinata per COGNOME\n\n") ;
  stampa_record( stdout, record, n_record ) ;

  /* ordina i record per matricola */
  qsort( record, n_record, sizeof(tipo_struttura), compare_matricola ) ;
  printf("Lista ordinata per MATRICOLA\n\n") ;
  stampa_record( stdout, record, n_record ) ;

  /* ordina i record per voto */
  qsort( record, n_record, sizeof(tipo_struttura), compare_voto ) ;
  printf("Lista ordinata per VOTO\n\n") ;
  stampa_record( stdout, record, n_record ) ;

  printf("Chiudo il file: %s\n",nome_file) ;
  err_code = fclose(descrittore_file) ;
  /* controllo se l'apertura del file ha avuto successo */  
  if ( err_code != 0 ) {
    perror("Ho trovato questo errore") ;
    exit(1) ; /* chiamata di sistema, uscita di brutto 
                 ripulisce un po tutto e chiude file eventualmente
                 aperti */
  }

  printf("Tutto fatto!\n") ;

  return 0 ;
}
