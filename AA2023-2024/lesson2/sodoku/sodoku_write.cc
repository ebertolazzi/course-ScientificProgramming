/*



*/

#include "sodoku.hh"

namespace Sodoku {

  static std::string top_left     = "\u250F";
  static std::string top_right    = "\u2513";
  static std::string bottom_left  = "\u2517";
  static std::string bottom_right = "\u251B";

  static std::string V  = "\u2503";
  static std::string H  = "\u2501";
  static std::string H7 = H+H+H+H+H+H+H;
  static std::string VC = " \u2503 ";
  static std::string VL = "\u2503 ";
  static std::string VR = " \u2503";

  static std::string C = "\u254B";

  static std::string TU = "\u2533";
  static std::string TD = "\u253B";
  static std::string TL = "\u2523";
  static std::string TR = "\u252B";

  static std::string EMPTY = "\u2218";

  static
  std::string
  to_char( int i ) {
    if ( i == 0 ) return "\u25A1";
    return std::to_string(i);
  }

  void
  write_table( int const table[9][9], std::basic_ostream<char> & stream ) {
    std::string line;
    for ( int i = 0; i < 9; ++i ) {
      if ( i == 0 ) {
        stream << top_left << H7 << TU << H7 << TU << H7 << top_right << "\n";
      } else if ( i % 3 == 0 ) {
       stream << TL << H7 << C << H7 << C << H7 << TR << "\n";
      }
      stream
        << VL  << to_char( table[i][0] )
        << " " << to_char( table[i][1] )
        << " " << to_char( table[i][2] )
        << VC  << to_char( table[i][3] )
        << " " << to_char( table[i][4] )
        << " " << to_char( table[i][5] )
        << VC  << to_char( table[i][6] )
        << " " << to_char( table[i][7] )
        << " " << to_char( table[i][8] )
        << VR  << "\n";
    }
    stream << bottom_left << H7 << TD << H7 << TD << H7 << bottom_right << "\n";
  }
}
