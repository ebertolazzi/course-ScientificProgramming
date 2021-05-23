#include <stdio.h>

// for malloc, calloc, free
#include <stdlib.h>

// standard controlled size integer
#include <stdint.h>

/*
  int8_t, int16_t, int32_t, nt64_t
  signed integer type with width of exactly 8, 16, 32 and 64
  bits respectively
  normally int == int32_t

  int_fast8_t, int_fast16_t, int_fast32_t, int_fast64_t
  fastest signed integer type with width of
  at least 8, 16, 32 and 64 bits respectively

  int_least8_t, int_least16_t, int_least32_t, int_least64_t
  smallest signed integer type with width of
  at least 8, 16, 32 and 64 bits respectively

  adding u in front --> unsigned version
  int_fast16_t --> uint_fast16_t
*/

static
void
print_binaryu( char header[], uint16_t i ) {
  char res[17] = "0000000000000000";
  int ipos = 0;
  printf("%s = %07d",header,i);
  while ( i > 0 ) {
    // fill the string in reverse order
    if ( i % 2 == 1 ) res[15-ipos] = '1';
    else              res[15-ipos] = '0';
    i = i/2; // i /= 2 compact form
    ++ipos;
  }
  printf("  %s = %s[binary]\n",header,res);
}
static
void
print_binary( char header[], int16_t isigned ) {
  uint16_t i = (uint16_t) isigned; // casting, reitepreto blocco di memoria
                                   // da intero senza segno a intero con segno
  print_binaryu( header, i );
}


int
main( int argc, char const *argv[] ) {
  int16_t   i16, i16b;
  uint16_t  u16, u16b;
  i16 = 123;
  print_binary("i16",i16);
  i16 = -123;
  print_binary("i16",i16);

  // bit operation:

  // complement
  printf("\n\nCOMPLEMENT <<\n");
  i16  = 2234;
  i16b = ~i16;
  print_binary("i16",i16);
  print_binary("~i16",i16b);

  // shift
  printf("\n\nSHIFT >>\n");
  i16  = ~0;
  i16b = i16<<3;
  print_binary("i16   ",i16);
  print_binary("i16<<3",i16b);

  i16  = ~0;
  i16b = i16>>2;
  print_binary("i16   ",i16);
  print_binary("i16>>2",i16b);

  // shift
  printf("\n\nSHIFT <<\n");
  u16  = ~0;
  u16b = u16<<3;
  print_binaryu("u16   ",u16);
  print_binaryu("u16<<3",u16b);

  u16  = ~0;
  u16b = u16>>2;
  print_binaryu("u16   ",u16);
  print_binaryu("u16>>2",u16b);

  // AND
  printf("\n\nAND\n");
  u16  = 1234;
  u16b = 4321;
  print_binaryu("u16       ",u16);
  print_binaryu("u16b      ",u16b);
  print_binaryu("u16 & u16b",u16 & u16b);

  // OR
  printf("\n\nOR\n");
  u16  = 1234;
  u16b = 4321;
  print_binaryu("u16       ",u16);
  print_binaryu("u16b      ",u16b);
  print_binaryu("u16 | u16b",u16 | u16b);

  // XOR
  printf("\n\nXOR\n");
  u16  = 1234;
  u16b = 4321;
  print_binaryu("u16       ",u16);
  print_binaryu("u16b      ",u16b);
  print_binaryu("u16 ^ u16b",u16 ^ u16b);

  // check if big enddian
  { // new block, can define new variable
    uint8_t  *fourbyte;
    uint32_t casted_int32 = 1;
    uint32_t *bad_pointer;
    fourbyte = (uint8_t*)&casted_int32; // convert pointer from 32 to 8 bit
    printf("fourbyte[0] = %d\n",(int)fourbyte[0]);
    printf("fourbyte[1] = %d\n",(int)fourbyte[1]);
    printf("fourbyte[2] = %d\n",(int)fourbyte[2]);
    printf("fourbyte[3] = %d\n",(int)fourbyte[3]);

    //
    bad_pointer = (uint32_t*)(fourbyte+1);
    printf("*bad_pointer = %d\n", *bad_pointer);
  }

  return 0;
}
