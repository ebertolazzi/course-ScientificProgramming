/*
 * Programma inutile che esegue i seguenti compiti:
 *
 * Legge da un file un elenco di nomi+matricola+voto
 * salva i record letti su una lista dinamicamante
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

typedef struct /* non serve il nome della struttura */ {
  char cognome[MAX_LEN] ;
  char nome[MAX_LEN] ;
  char matricola[MATRICOLA_LEN] ;
  int  voto ;
} tipo_struttura ;

typedef struct _elemento_lista_struttura {
  tipo_struttura il_record ;
  struct _elemento_lista_struttura * prossimo ;
  /* puntatore a una struttura dello stesso tipo che sto
     definendo */
} elemento_lista_struttura ;

/* il puntatore al primo elemento della lista e' la lista */
static elemento_lista_struttura * lista_struttura ;

static 
void
Inizializza() {
  lista_struttura = NULL ; /* inizializzo alla lista vuota */
}

static
void
Inserisci_in_testa_alla_lista(tipo_struttura const * record_pointer ) {
  /* allocazione dinamica di un nuovo elemento della lista */
  elemento_lista_struttura * nuovo_elemento ;
  nuovo_elemento = malloc(sizeof(elemento_lista_struttura)) ;
  /* bisogna controllare che l'allocazione vada a buon fine */
  /* da fare ..... */
   
  /* copia del record bit a bit */
  memcpy( & nuovo_elemento -> il_record, /* puntatore memoria di arrivo */
          record_pointer,                /* puntatore memoria di partenza */
          sizeof(tipo_struttura) ) ;     /* quanti byte copiare */

  /* inserisco in testa alla lista questo elemento */
  if ( lista_struttura == NULL ) {
    /* la lista e' vuota, nuovo_elemento e' la lista di un solo
       elemento */
    nuovo_elemento -> prossimo = NULL ;
    lista_struttura = nuovo_elemento ;
  } else {	
    /* la lista c'e' gia, aggiungo in testa alla lista */
    nuovo_elemento -> prossimo = lista_struttura ;
    lista_struttura = nuovo_elemento ;
  }
}

static
void
Distruggi_la_lista() {
  elemento_lista_struttura * prossimo ; 
  while ( lista_struttura != NULL ) {
	prossimo = lista_struttura -> prossimo ;
	/* salvo il puntatore al prossimo elemento della lista */
    free( lista_struttura ) ; /* riliascio la memoria allocata */
	lista_struttura = prossimo ;
	/* non si puo scrivere lista_struttura = lista_struttura -> prossimo 
	   perche' il puntatore a lista struttura e' stato rilasciato
	   e quindi non e' garatito che il record sia ancora in memoria */
  }
}

/*
 * Altre funzioni possibili da definire:
 *
 * Contare quanto elementi della lista ci sono
 * Inserisci in coda alla lista
 * Inserisci alla posizione n della lista
 * Costruire una lista nell'ordine inverso
 * Data lista costruire un vettore (allocato alla dimensione giusta)
 * e poi riempirlo e ordinarlo.
 */

/*
 * Possibili miglioramenti
 *  che succede con i doppi cognomi ?
 *  si puo' modificare il codice in modo che funzioni sempre correttamente ?
 */

static
void
Stampa_la_lista(FILE * fd) {
  elemento_lista_struttura * elemento = lista_struttura ; 
  tipo_struttura           * ps ;
  int n_record = 0 ;
  while ( elemento != NULL ) {
    /* uso l'elemnto della lista */
    ps = & elemento -> il_record ; /* estraggo il puintatore al record */
    fprintf(fd,
            "Record n. %d\n"
            "  Cognome:   %s\n"	
            "  Nome:      %s\n"	
            "  Matricola: %s\n"	
            "  Voto:      %d\n",
            n_record++, /* uso il valore e solo dopo l'uso lo incremento */
            ps -> cognome,
            ps -> nome,
            ps -> matricola,
            ps -> voto) ;
   
   /* passo al prossimo elemento della lista */
   elemento = elemento -> prossimo ;
  }
}

int
main () {
  int            err_code ; /* usato per il codice di errore restituito dall I/O */
  char           nome_file[100] ;
  FILE *         descrittore_file ;
  tipo_struttura un_record ;
  
  printf("NOME FILE ?:") ;
  scanf("%s",nome_file) ;
  printf("Apro il file: %s\n",nome_file) ;
  descrittore_file = fopen ( nome_file, "r" );

  /* controllo se l'apertura del file ha avuto successo */  
  if ( descrittore_file == NULL ) {
    perror("Ho trovato questo errore") ;
    exit(1) ;
  }

  Inizializza() ; /* inizializzo la lista alla lista vuota */

  /*
   * voglio saltare la prima riga che contine un commento
   */
  { /* apro nuovo blocco */
    int ch ; /* posso definire nuove variabili */
    while ( ( ch = fgetc(descrittore_file) ) != '\n' &&
              ch != EOF ) /* messuna istruzione */ ;
  }
  /* ch non e' piu' visibile */  

  while ( fscanf(descrittore_file,
                "%s%s%s%d",
                un_record.cognome,
                un_record.nome,
                un_record.matricola,
                & un_record.voto ) == 4 ) {
    /* inserisci il record in testa alla lista */
    Inserisci_in_testa_alla_lista( & un_record ) ;
       /* uso & per passare il puntatore al record e non il record stesso */ 
  }

  printf("Chiudo il file: %s\n",nome_file) ;
  err_code = fclose(descrittore_file) ;
  /* controllo se l'apertura del file ha avuto successo */  
  if ( err_code != 0 ) {
    perror("Ho trovato questo errore") ;
    exit(1) ; /* chiamata di sistema, uscita di brutto 
                 ripulisce un po tutto e chiude file eventualmente
                 aperti */
  }

  Stampa_la_lista ( stdout ) ;
  Distruggi_la_lista() ;
  
  printf("Tutto fatto!\n") ;

  return 0 ;
}
