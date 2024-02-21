cmake_minimum_required(VERSION 3.5)
project(Sudoku)

# add the data to the target, so it becomes visible in some IDE
add_executable( Sudoku Sudoku_main.cc Sudoku_read.cc Sudoku_write.cc Sudoku_solve.cc )

set_target_properties( Sudoku PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS off )

#
# to generate a makefile use
#
# cmake -G "Unix Makefiles" .
#
# to generate a ninja project
#
# cmake -G "Ninja" .
#
#
#
