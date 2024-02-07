/*
example of ineheritance in C++11

*/

// standard header for I/O
#include <iostream>

// standard header C++ strings
#include <string>

// for timing
#include <chrono>

// for thread and in particular the function sleep_for
#include <thread>

#include <map>

// try catch standard error classes
#include <exception>

using namespace std;

int
main() {

  try {

  // key=string and value=double for a map
  map<string,int> M;

  // create an elemet in the map
  M["pippo"] = 123;

  M.insert( pair<string,double>("pluto",234) );

  M.insert( make_pair("paperino",-234) );

  // wrong make a pair of character and double
  // M.insert( make_pair('c',-234.0) );
  M.insert( make_pair("zippo",-234.3455) );

  // M["wrong"] = 123.4;

  for ( auto const & e : M )
    cout << "M[\"" << e.first << "\"] = " << e.second << '\n';

  cout << "M['pippo'] = " << M["pippo"] << '\n';
  cout << "M['zagor'] = " << M["zagor"] << '\n';
  try {
    cout << "M.at['zagor2'] = " << M.at("zagor2") << '\n';
  } catch ( exception const & e ) {
    throw runtime_error( string("M.at['zagor2'] ") + e.what() );
  }
  } catch ( exception const & e ) {
    cout << "\n\nError: " << e.what() << '\n';
  }
  return 0;
}
