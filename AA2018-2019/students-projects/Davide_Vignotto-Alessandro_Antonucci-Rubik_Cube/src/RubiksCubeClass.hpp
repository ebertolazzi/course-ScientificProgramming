/* ============================================================================

Name   : RubiksCubeClass.hpp
Authors: Alessandro Antonucci and Davide Vignotto
         University of Trento

         Class that stores, shuffles and solves a 3x3x3 Rubik's cube.
         PhD course of Scientific Programming - prof. Bertolazzi.

===============================================================================
      ___           ___       ___           ___           ___           ___     
     /\  \         /\__\     /\  \         /\  \         /\  \         /\__\    
    /::\  \       /:/  /    /::\  \       /::\  \       /::\  \       /:/  /    
   /:/\:\  \     /:/  /    /:/\:\  \     /:/\:\  \     /:/\:\  \     /:/  /     
  /::\~\:\  \   /:/  /    /::\~\:\  \   /:/  \:\__\   /::\~\:\  \   /:/__/  ___ 
 /:/\:\ \:\__\ /:/__/    /:/\:\ \:\__\ /:/__/ \:|__| /:/\:\ \:\__\  |:|  | /\__\
 \/__\:\/:/  / \:\  \    \:\~\:\ \/__/ \:\  \ /:/  / \/__\:\/:/  /  |:|  |/:/  /
      \::/  /   \:\  \    \:\ \:\__\    \:\  /:/  /       \::/  /   |:|__/:/  / 
      /:/  /     \:\  \    \:\ \/__/     \:\/:/  /        /:/  /     \::::/__/  
     /:/  /       \:\__\    \:\__\        \::/__/        /:/  /       ~~~~      
     \/__/         \/__/     \/__/         ~~            \/__/                  

===============================================================================

Class description

Given a solved 3x3x3 Rubik's cube, we define its "faces" in this way:

WHITE  ==> UPPER FACE "U"
YELLOW ==> DOWN  FACE "D"
GREEN  ==> FRONT FACE "F"
BLUE   ==> BACK  FACE "B"
RED    ==> RIGHT FACE "R"
ORANGE ==> LEFT  FACE "L"

Each face is composed by nine smaller faces, which we call "elements".
Each element is associated to a number, from 0 to 53. The state of the
cube is the vector containing these numbers, when the cube is solved, the vector
is sorted from 0 to 53.

The cube is composed by 27 pieces, that are the small cubes having the elements
as faces.

The different moves that can be applyied to a cube are just 12, two for each
face (clockwise and counterwise). An upper case letter defines a 90 degree clockwise move.
A lower case defines a counterclockwise move.
Examples: U -> move upper face 90 degrees clockwise
          b -> move back  face 90 degrees counterclockwise

The solving algorithm acts in human-like way: it solves the cube layer by layer, starting
from up face (white) to down face (yellow).

============================================================================ */


#include <vector> 
#include <string> 
#include <map>     

using namespace std;

class RubiksCube {

  int                        move_count;  // Counter of the number of moves
  std::string                move_seq;    // String containing sequence of moves
  std::vector<int>           state;       // State of the cube (54 elements vector of integers)
  std::map<std::string, int> mymap_si = { 
    { "F" ,  1 },
    { "f",  2 },
    { "R" ,  3 },
    { "r",  4 },
    { "U" ,  5 },
    { "u",  6 },
    { "B" ,  7 },
    { "b",  8 },
    { "L" ,  9 },
    { "l", 10 },
    { "D" , 11 },
    { "d", 12 }
  };                                      // Map to convert moves from integer to char
  std::map<int, std::string> mymap_is = {
    {  1, "F"  },
    {  2, "f" },
    {  3, "R"  },
    {  4, "r" },
    {  5, "U"  },
    {  6, "u" },
    {  7 ,"B"  },
    {  8, "b" },
    {  9, "L"  },
    { 10, "l" },
    { 11, "D"  },
    { 12, "d" }
  };                                      // Map to convert moves from char to integer

  // Searching where is the element "a" in the state 
  int search_pos(int a);

  // Searching in which face of the cube is element "a"
  string search_face(int a);
  
  // Search in which layer of the cube is element "a"
  int search_layer(int a);    // 1-2-3 from TOP to DOWN
  int search_layer_BF(int a); // 1-2-3 from FRONT to BACK
  int search_layer_LR(int a); // 1-2-3 from LEFT to RIGHT

  // Bring the piece containing the element "a" to the down layer
  void bring_down_angle(int a);
  void bring_down_edge(int a);

  // Defining the inverse of a given move
  string inv(string f);

  // Defining how a move permutate elements
  void permut(int a, int b, int c, int d);

  // Applying a move on the state given the relative move name
  void single_move(string which_face);

  /* ================ Solving methods ================ */

  // Solve the white cross
  void white_cross();

  // Solve the white angles
  void white_angles();

  // Solve the middle edges
  void middle_edges();

  // Solve the yellow cross
  void yellow_cross();
  
  // Solve yellow angles
  void yellow_angles();

public:

  // Constructor: initialize the state
  RubiksCube();

  // Destructor: clear the instance
  ~RubiksCube();

  // Return the actual state of the cube
  vector<int> get_state();

  // Shuffle the cube by applying "n" random moves
  void rand_shuffle(int n , string & move_seq);

  // Apply a move or a sequence of moves 
  void move(string s);

  // Solve the cube
  bool solve(int & mc , string & ms);
  
  // Print the state
  void print();
  
  // Main method
  void is_this_water();

};