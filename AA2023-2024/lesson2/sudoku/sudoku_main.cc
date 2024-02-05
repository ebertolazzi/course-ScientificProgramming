#include "sudoku.hh"


int
main() {
  int table[9][9];

  Sudoku::read_table( "problem.txt", table );
  std::cout << "The problem:\n\n";
  Sudoku::write_table( table, std::cout );
  std::cout << "Solve problem:\n\n";
  Sudoku::solve( table );
  std::cout << "The solution:\n\n";
  Sudoku::write_table( table, std::cout );
  std::cout << "All done folks!!\n";
  return 0;
}