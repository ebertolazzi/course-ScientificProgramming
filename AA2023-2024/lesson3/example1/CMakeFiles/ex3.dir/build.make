# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1

# Include any dependencies generated for this target.
include CMakeFiles/ex3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ex3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ex3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3.dir/flags.make

CMakeFiles/ex3.dir/ex3.cc.o: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/ex3.cc.o: ex3.cc
CMakeFiles/ex3.dir/ex3.cc.o: CMakeFiles/ex3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex3.dir/ex3.cc.o"
	/Applications/Xcode-15.2.0.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ex3.dir/ex3.cc.o -MF CMakeFiles/ex3.dir/ex3.cc.o.d -o CMakeFiles/ex3.dir/ex3.cc.o -c /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1/ex3.cc

CMakeFiles/ex3.dir/ex3.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ex3.dir/ex3.cc.i"
	/Applications/Xcode-15.2.0.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1/ex3.cc > CMakeFiles/ex3.dir/ex3.cc.i

CMakeFiles/ex3.dir/ex3.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ex3.dir/ex3.cc.s"
	/Applications/Xcode-15.2.0.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1/ex3.cc -o CMakeFiles/ex3.dir/ex3.cc.s

# Object files for target ex3
ex3_OBJECTS = \
"CMakeFiles/ex3.dir/ex3.cc.o"

# External object files for target ex3
ex3_EXTERNAL_OBJECTS =

ex3: CMakeFiles/ex3.dir/ex3.cc.o
ex3: CMakeFiles/ex3.dir/build.make
ex3: CMakeFiles/ex3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3.dir/build: ex3
.PHONY : CMakeFiles/ex3.dir/build

CMakeFiles/ex3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex3.dir/clean

CMakeFiles/ex3.dir/depend:
	cd /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1 /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1 /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1 /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1 /Users/enrico/Didattica_corsi/Didattica-GITHUB/github-ScientificProgramming/AA2023-2024/lesson3/example1/CMakeFiles/ex3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ex3.dir/depend

