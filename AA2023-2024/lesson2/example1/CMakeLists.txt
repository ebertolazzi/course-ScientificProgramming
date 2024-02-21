cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_VERBOSE_MAKEFILE ON)
# choode C++11 as stanadard for compilation
set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# add the data to the target, so it becomes visible in some IDE
add_executable( ex1 ex1.cc )
add_executable( ex2 ex2.cc )
add_executable( ex3 ex3.cc )
add_executable( ex4 ex4.cc )
add_executable( ex5 ex5.cc )
add_executable( ex6 ex6.cc )
add_executable( ex7 ex7.cc )


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
