#include "sodoku.hh"


int
main() {
  int table[9][9];

  Sodoku::read_table( "problem.txt", table );
  std::cout << "The problem:\n\n";
  Sodoku::write_table( table, std::cout );
  std::cout << "Solve problem:\n\n";
  Sodoku::solve( table );
  std::cout << "The solution:\n\n";
  Sodoku::write_table( table, std::cout );
  std::cout << "All done folks!!\n";
  return 0;
}