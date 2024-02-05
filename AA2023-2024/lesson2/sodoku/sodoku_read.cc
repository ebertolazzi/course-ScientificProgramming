/*



*/

#include "sodoku.hh"

#include <fstream>

namespace Sodoku {

  static
  int
  get_number( char ch ) {
    if ( ch == '.' ) return 0;
    return int(ch-'0');
  }

  void
  read_table( std::string const & file_name, int table[9][9] ) {
    std::ifstream file(file_name.c_str());
    if ( !file ) {
      std::cerr << "Cannot open file: " << file_name << "\n";
      std::exit(0);
    }
    std::string line;
    for ( int i = 0; i < 9; ++i ) {
      if ( i % 3 == 0 ) std::getline( file, line );
      std::getline( file, line );

      table[i][0] = get_number( line[2] );
      table[i][1] = get_number( line[4] );
      table[i][2] = get_number( line[6] );

      table[i][3] = get_number( line[10] );
      table[i][4] = get_number( line[12] );
      table[i][5] = get_number( line[14] );

      table[i][6] = get_number( line[18] );
      table[i][7] = get_number( line[20] );
      table[i][8] = get_number( line[22] );

    }
    file.close();
  }
}

/*
+-------+-------+-------+
| 2 . . | 1 . 5 | . . 3 |
| . 5 4 | . . . | 7 1 . |
| . 1 . | 2 . 3 | . 8 . |
+-------+-------+-------+
| 6 . 2 | 8 . 7 | 3 . 4 |
| . . . | . . . | . . . |
| 1 . 5 | 3 . 9 | 8 . 6 |
+-------+-------+-------+
| . 2 . | 7 . 1 | . 6 . |
| . 8 1 | . . . | 2 4 . |
| 7 . . | 4 . 2 | . . 1 |
+-------+-------+-------+
*/
