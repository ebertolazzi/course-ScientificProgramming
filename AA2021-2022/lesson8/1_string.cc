#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

// string library (C version)
#include <string.h>

// string object (C++ version)
#include <string>

// for sort
#include <algorithm>

using namespace std ;

int
main() {
  cout << "Digit 0\n";
  cout << "Digit \x30\n";

  cout << "Letter ~\n";
  cout << "Letter \x7E\n";

  char const * a_C_string = "I am a string"; // pointer to a constant piece of memory
  for ( int i = 0 ; i <= strlen(a_C_string) ; ++i )
    cout << i << "-th character is: "
         << a_C_string[i]
         << " hex: " << hex << int(a_C_string[i]) << dec // reset to decimal
         << '\n' ; 

  string a_Cpp_string = "I am a string";
  
  cout << "C++ string: " << a_Cpp_string << '\n';
  cout << "length: " << a_Cpp_string.length() << '\n';
  sort( a_Cpp_string.begin(), a_Cpp_string.end() );
  cout << "Sorted: " << a_Cpp_string << '\n';
  reverse( a_Cpp_string.begin(), a_Cpp_string.end()) ;
  cout << "Reversed: " << a_Cpp_string << '\n' ;

  string str1 = "I am string1" ; 
  string str2 = "I am string2" ; 
  string str = str1 + str2 ;
  
  cout << "Concatenated: " << str << '\n' ;
  cout << "str[1] " << str[1] << '\n' ;
  cout << "str[5] " << str[5] << '\n' ;
  cout << "str[3] " << str[3] << '\n' ;

  str1 = "INITIAL STRING" ;
  cout << "str1 = " << str1 << '\n' ;
  str1.push_back('p');
  cout << "str1 = " << str1 << '\n' ;
  str1.push_back('i');
  cout << "str1 = " << str1 << '\n' ;
  str1.push_back('p');
  cout << "str1 = " << str1 << '\n' ;
  str1.push_back('p');
  cout << "str1 = " << str1 << '\n' ;
  str1.push_back('o');
  cout << "str1 = " << str1 << '\n' ;

  str1.pop_back();
  cout << "str1 = " << str1 << '\n' ;
  str1.pop_back();
  cout << "str1 = " << str1 << '\n' ;
  str1.pop_back();
  cout << "str1 = " << str1 << '\n' ;
  str1.pop_back();
  cout << "str1 = " << str1 << '\n' ;
  str1.pop_back();
  cout << "str1 = " << str1 << '\n' ;

  str1.erase( 4, 30 );
  cout << "str1[ - 4th character + 3] = " << str1 << '\n' ;

  return 0 ;
}

