// tell the compiler to include only one time
#pragma once

// if pragma is not known by the compiler
// old way to avoid double inclusion

#ifndef SIEVE_HH
#define SIEVE_HH

#include <vector>
#include <iostream>

// prototype of the function Sieve
std::vector<int> Sieve( int N );

// pretty print
void Sieve_print( std::vector<int> const &, std::basic_ostream<char> &, int M = 15 );

#endif
