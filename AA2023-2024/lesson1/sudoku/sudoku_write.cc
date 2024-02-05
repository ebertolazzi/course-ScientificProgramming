/*



*/

#include "sudoku.hh"

namespace Sudoku {


  static
  char
  to_char( int i ) {
    if ( i == 0 ) return '.';
    return int('0'+i);
  }

  void
  write_table( int const table[9][9], std::basic_ostream<char> & stream ) {
    std::string line;
    for ( int i = 0; i < 9; ++i ) {
      if ( i % 3 == 0 ) stream << "+-------+-------+-------+\n";
      stream
        <<  "| " << to_char( table[i][0] )
        <<   " " << to_char( table[i][1] )
        <<   " " << to_char( table[i][2] )
        << " | " << to_char( table[i][3] )
        <<   " " << to_char( table[i][4] )
        <<   " " << to_char( table[i][5] )
        << " | " << to_char( table[i][6] )
        <<   " " << to_char( table[i][7] )
        <<   " " << to_char( table[i][8] )
        <<   " |\n";
    }
    stream << "+-------+-------+-------+\n";
  }
}
