cmake_minimum_required(VERSION 3.0)
project(Sodoku)

# add the data to the target, so it becomes visible in some IDE
add_executable( Sodoku Sodoku_main.cc Sodoku_read.cc Sodoku_write.cc Sodoku_solve.cc )

set_target_properties( Sodoku PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS off )

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
