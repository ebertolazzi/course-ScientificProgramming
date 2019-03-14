/*
  Convert a number to a string.
  For example
  
  123456 = one hundred and twenty three thousads and four hundred and fifty six

*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
    
using namespace std ;

typedef int indexType ;

void
splitDigit( indexType           number, 
            vector<indexType> & digits ) {
  digits.clear() ;
  while ( number > 0 ) {
    digits . push_back(number % 10) ;
    number /= 10 ;
  }
}

// the first 20 number

string num0to19[] = {
  "",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eightteen",
  "nineteen"
} ;

string num10to100[] = {
  "",
  "ten",
  "twenty",
  "thity",
  "fourty",
  "fifty",
  "sixty",
  "sevety",
  "eighty",
  "ninety"
} ;


// convert number from 0 to 999
string
num3digitToString( indexType num ) {
  indexType n = num%100 ;
  string res = "" ;
  if ( n < 20 ) res = num0to19[n] ;
  else          res = num10to100[n/10]+" "+ num0to19[n%10] ;
  indexType c = (num/100) % 10 ;
  if ( c > 0 ) {
    if ( n > 0 ) res = num0to19[c] + " hundred and " + res ;
    else         res = num0to19[c] + " hundred " ;
  }
  return res ;
}

// convert number collect 3 digits at iteration
string
numToString( indexType n ) {

  // special case n = 0 
  if ( n == 0 ) return "zero" ;

  string tmb[] = { " ", " thousads ", " millions ", " billions " } ;
  string res   = "" ;
  
  for ( indexType k = 0 ; n > 0 ; n /= 1000, ++k ) {
    string num = num3digitToString( n ) ;
    if ( num . length() > 0 && res . length() > 0 ) res = "and " + res ;
    if ( num . length() > 0 ) res = num + tmb[k] + res ;
  }
  return res ;
}


int
main() {
  vector<indexType> digits ;
  indexType         num = 123456 ;
  splitDigit( num, digits ) ;
  cout << "Split digits for " << num << "=" ; 
  copy( digits.begin(), digits.end(),
        ostream_iterator<indexType>(cout, ":") ) ;
  
  cout << '\n' ;
  indexType nums[] = {100, 1000, 1000000, 123, 123456, 10000001, 0, -1 } ;
  for ( indexType i = 0 ; nums[i] >= 0 ; ++i ) {
    cout << setw(10) << nums[i] << " = " << numToString(nums[i]) << '\n' ;
  }

}
