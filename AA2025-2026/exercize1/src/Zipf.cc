#include "Zipf.hh"


void
add_word( std::string const & w, std::map<std::string,int> & m ) {
  // check if w is into m
  auto res = m.find(w);
  if ( res != m.end() ) {
    ++res->second; // increment
  } else {
    m[w] = 1;
  }
}

bool is_letter_or_italian_accent( std::string const & s ) {
  if ( s.size() == 1 ) {
    char c = s[0];
    return ( c >= 'a' && c <= 'z' ) ||
           ( c >= 'A' && c <= 'Z' );

  }

  return s == "à" || s == "è" || s == "é" ||
         s == "ì" || s == "ò" || s == "ù" ||
         s == "À" || s == "È" || s == "É" ||
         s == "Ì" || s == "Ò" || s == "Ù";
}

/* optimized */
/*
void
add_word( std::string const & w, std::map<std::string,int> & m ) {
  ++m[w];
}
*/

/*
  command arg1 arg2 ...
  
  argc = number of argument+1
  argv[] = { "command", "art1", ... }
*/
int
main( int argc, char *argv[] ) {

  std::map<std::string,int> words;

  if ( argc != 2 ) {
    std::cerr << "Usage: " << argv[0] << " file!\n";
    return 1;
  }
  
  std::string file_name = argv[1]; // copy file name to string file_name
  
  std::ifstream file( file_name );
  std::string line;

  while ( std::getline( file, line ) ) {
    // here line contains one full line from the file
    std::cout << line << '\n';
    // update words
    std::string w;
    for ( auto c : line ) {
      if ( is_letter_or_italian_accent( c ) ) {
        w += c;
      } else {
        if ( w.length() > 1 ) add_word( w, words );
        w = "";
      }
    }
  }
  
  file.close();

  std::cout << "All done folks!\n";
  return 0;
}
