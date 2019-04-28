/* ===========================================================================

Name   : main.cpp
Authors: Alessandro Antonucci and Davide Vignotto
         University of Trento

         Shuffles and solves a 3x3x3 Rubik's cube.
         PhD course of Scientific Programming - prof. Bertolazzi.

=========================================================================== */

// Libraries
#include <iostream>
#include <vector>   // std::vector
#include <ctime>    // time

// Include Rubiks Class
#include "RubiksCubeClass.hpp"

// Namespace
using namespace std;

int main() {

  int rand_moves = 24; // Number of shuffling moves
  int num_moves;       // Number of solving moves

  // Seeding the random function "rand", used in method "rand_shuffle"
  srand(time(NULL));
  
  // Create a cube class instance
  RubiksCube cube;
  
  // Shuffling and solving the cube for n times
  for (int i = 0; i < 100; i++) {
    printf("%3.0d-th iteration - ", i+1 );
    
    // Shuffling randomly the cube
    string s1; // Sequence of shuffling moves
    cube.rand_shuffle(rand_moves, s1);

    // Solving the cube
    string s2; // Sequence of solving moves
    if ( cube.solve( num_moves , s2) ) {
      cout << "Solved in " << num_moves << " moves\n";
    }  else {
      cout << "Cube not solved!\n";
      break;
    }
  }

  cout << "\nDone!\n";
  return 0;

}