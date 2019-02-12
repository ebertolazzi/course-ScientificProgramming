/*
  example of use exception

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include <string> // C++ string

#include <exception>      // std::exception

using namespace std;

void
throw_an_exception_level_1() {
  cout << "Before the exception\n";
  //throw "SOMETHING GO WRONG" ;
  //throw 1234 ;
  throw runtime_error("runtime_error used");
  cout << "After the exception\n";
}

void
throw_an_exception() {
  cout << "Before throw_an_exception_level_1\n";
  throw_an_exception_level_1() ;
  cout << "After throw_an_exception_level_1\n";
}

int
main() {

  try {
    throw string("PIPPO");
    // ....
    cout << "Before the call of throw_an_exception()\n";
    throw_an_exception();
    cout << "After the call of throw_an_exception()\n";
    // ....
  }
  catch ( char const error[] ) {
    cerr << "Exception (char const error[]) found: " << error << "\n";
  }
  catch ( string const & error ) {
    cerr << "Exception (string const &) found: " << error << "\n";
  }
  catch ( int error ) {
    cerr << "Exception (inr) " << error << "\n"  ;
  }
  catch ( exception const & error ) {
    cerr << "Exception (exception const &) " << error.what() << "\n"  ;
  }
  catch ( ... ) {
    cerr << "Exception (...): Unknown error\n"  ;
  }
  cout << "END OF PROGRAM\n" ;

  return 0 ;
}

