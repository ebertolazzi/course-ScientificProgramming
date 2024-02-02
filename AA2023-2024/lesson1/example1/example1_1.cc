/*
  I am a multiline comment
*/

// I am a single line comment

/*

A body o a C/C++ program is a function "main" like the following

int
main( ) {


  return 0;
}

*/

// include the definition of the function of the standard library for I/O in C++
#include <iostream>

// include the definition of the function of the standard library for I/O in C
#include <stdio.h>

namespace I_am_a_namespace {
  int
  I_am_a_procedure( int a ) {
    return a+1;
  }

}

int
main( ) {

  // to run I_am_a_procedure from namespace I_am_a_namespace you must
  // call it with I_am_a_namespace::I_am_a_procedure

  int a = 1;
  int b = I_am_a_namespace::I_am_a_procedure( a );

  // or extract the function from namespace
  using I_am_a_namespace::I_am_a_procedure;
  int c = I_am_a_procedure( a );

  // or extral the whole namespace (all the functions defined inside)
  using namespace I_am_a_namespace;

  // C++ standard cout = object for the standard stream
  // std:: is the prefix for the namespace of the standard C++ library
  std::cout << "Hello world\n";

  // use the old C function for I/O
  printf( "Hello world\n" );

  std::cout << "All done folks!!\n";
  return 0;
}

/*
 To compile and run the code

 g++ example1.cc -o example1
 ^      ^           ^
 |      |           + name of the executable
 |      + name of file to be compiled
 + call the c++ compiler

  g++            is the name of the GNU compiler on LINUX OS
  g++ or clang++ is the name of the compiler on MAC OS
  cl.exe         is the name of the Visual Studio C++ compiler on WINDOWS

  cl.exe example1.cc /Fexample1

*/