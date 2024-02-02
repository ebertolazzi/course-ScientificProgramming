/*



*/

#pragma once
#ifndef SODOKU_HH
#define SODOKU_HH

#include <iostream>
#include <string>

namespace Sodoku {
  void read_table( std::string const & file_name, int table[9][9] );
  void write_table( int const table[9][9], std::basic_ostream<char> & stream );
  void solve( int table[9][9] );
}

#endif
