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

class no_copy_string : public string {
public:
  no_copy_string( no_copy_string const & ) = delete;

  no_copy_string( string const & s )
  { *static_cast<string*>(this) = s; };
};

int
main() {

  try {

  // key=string and value=double for a map
  map<no_copy_string,int> M;
  // create an elemet in the map
  no_copy_string str("pippo");
  // M[str] = 123; // compilation error, missing copy constructor

  } catch ( exception const & e ) {
    cout << "\n\nError: " << e.what() << '\n';
  }
  return 0;
}
