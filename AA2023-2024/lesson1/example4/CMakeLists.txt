cmake_minimum_required(VERSION 3.0)
project(Eratostene)

# add the data to the target, so it becomes visible in some IDE
add_executable( Eratosthenes1 Eratosthenes1.cc )
add_executable( Eratosthenes2 Eratosthenes2.cc Sieve.cc )

set_target_properties( Eratosthenes1 PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS off )
set_target_properties( Eratosthenes2 PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS off )

#
# to generate a makefile use
#
# cmake -G "Unix Makefiles" .
#
# to generate a ninja project
#
# cmake -G "Ninja" .
#
#
#
