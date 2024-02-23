#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/ostream.h>

#include <iostream>

int
main() {

  double a{1.33334};
  float b{1.234};

  fmt::print( "a = {}, b = {}\n", a, b );

  fmt::print( "a = {:8.2}, b = {}\n", a, b );
  fmt::print( std::cerr, "a = {:^8.2}, b = {}\n", a, b );
  fmt::printf( "a = %8.4f, b = %f\n", a, b );

  std::string str = fmt::format( "INTO A STRING a = {:8.2}, b = {}\n", a, b );

  std::cerr << str << "\n";

  fmt::print( "That all folks!!\n" );
  return 0;
}
