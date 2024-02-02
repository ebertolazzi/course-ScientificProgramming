#include "Sieve.hh"
#include <iostream>
#include <sstream>

//
// static = function visible onli in this units
//
static
int
parse_command( int argc, char const *argv[] ) {

  // count the aguments, must be 2!
  if ( argc != 2 ) {
    std::cout << "command: " << argv[0] << "s N\nexpected 1 more argument found " << argc-1 << "\n";
    std::exit(0);
  }

  // parse the command
  std::istringstream stream(argv[1]);
  int N;
  stream >> N; // read "the string"

  return N;
}

/*

   command ARGUMENTS

   argc = number of argumenst+1 (command is an argument)
   argv = vector od pointer to C-string with the arguments

   pippo 1 2 pluto

   argc = 4
   argv[0] = "pippo"
   argv[1] = "1"
   argv[2] = "2"
   argv[3] = "pluto"

*/
int
main( int argc, char const *argv[] ) {

  int  N = parse_command( argc, argv );

  std::vector<int> primes = Sieve( N );
  Sieve_print( primes, std::cout );

  std::cout << "There are " << primes.size() << " prime number in the range [1," << N << "]\n";
  std::cout << "All done folks!!\n";

  return 0;
}
