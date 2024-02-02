cmake_minimum_required(VERSION 3.0)
project(example3)

# add the data to the target, so it becomes visible in some IDE
add_executable( example3_1 example3_1.cc )

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
