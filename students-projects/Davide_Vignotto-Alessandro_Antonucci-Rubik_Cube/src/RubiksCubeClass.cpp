/* ===========================================================================

Name   : RubiksCubeClass.cpp
Authors: Alessandro Antonucci and Davide Vignotto
         University of Trento

         Class that stores, shuffles and solves a 3x3x3 Rubik's cube.
         PhD course of Scientific Programming - prof. Bertolazzi.

==============================================================================
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

=========================================================================== */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctype.h>

#include "RubiksCubeClass.hpp"

using namespace std;

// Constructor: initialize the state: ordered cube
RubiksCube::RubiksCube () {
  for (int i = 0; i < 54; i++) state.push_back(i);
}

// Destructor
RubiksCube::~RubiksCube() {
}

// Return the actual state of the cube
vector<int> RubiksCube::get_state() {
  return state;
}

// Shuffle the cube by applying n random moves
void RubiksCube::rand_shuffle(int n , string & ms) {
  move_seq.clear();
  for (int i = 0 ; i < n ; i++) {
      int choosen_move = ( rand()  % 12 ) + 1; // choosing a random move
      string a = mymap_is.find(choosen_move) -> second;
      this -> move(a); // actually moving the cube
  }
  ms = move_seq;
  move_seq.clear();
}
     
// Apply a move or a sequence of moves
void RubiksCube::move(string s) {
  string buffer;
  // Parse string of moves
  for (int i = 0; i < s.length(); ++i) {
    if ( s[i] == 'F' || s[i] == 'R' || s[i] == 'L' || s[i] == 'D' || s[i] == 'U' || s[i] == 'B' ||
         s[i] == 'f' || s[i] == 'r' || s[i] == 'l' || s[i] == 'd' || s[i] == 'u' || s[i] == 'b'    ) {
      buffer = s[i];
      this -> single_move(buffer);
    }
  }
}

// Searching where is the element "a" in the state  
int RubiksCube::search_pos(int a){
    vector<int>::iterator it = find(state.begin(), state.end(), a);
    return distance(state.begin(),it);
}

// Searching in which face of the cube is element "a" 
string RubiksCube::search_face(int a) {
  switch (search_pos(a)) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
      return "U";
      break;
    case 9: case 10: case 11: case 21: case 22: case 23: case 33: case 34: case 35:
      return "L";
      break;
    case 12: case 13: case 14: case 24: case 25: case 26: case 36: case 37: case 38:
      return "F";
      break;
    case 15: case 16: case 17: case 27: case 28: case 29: case 39: case 40: case 41:
      return "R";
      break;
    case 18: case 19: case 20: case 30: case 31: case 32: case 42: case 43: case 44:
      return "B";
      break;
    case 45: case 46: case 47: case 48: case 49: case 50: case 51: case 52: case 53:
      return "D";
      break;
    default:
      return "Error in search_face()";
      return "WRONG FACE";
      break;
  }
}

// Search in which layer from TOP to DOWN of the cube is element "a" 
int RubiksCube::search_layer(int a) {
  switch (search_pos(a)) {
    case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8:
    case  9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17:
    case 18: case 19: case 20:
      return 1;
      break;
    case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
    case 30: case 31: case 32:
      return 2;
      break;
    case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41:
    case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49: case 50: 
    case 51: case 52: case 53:     
      return 3;
      break;
    default:
      cout << "Error in search_layer()";
      return -1; // error
      break;
  }
}

// Search in which layer from BACK to FRONT of the cube is element "a" 
int RubiksCube::search_layer_BF(int a) {
  switch (search_pos(a)) {
    case  6: case  7: case  8: case 11: case 12: case 13: case 14: case 15: case 23:
    case 24: case 25: case 26: case 27: case 35: case 36: case 37: case 38: case 39:
    case 45: case 46: case 47:
      return 3;
      break;
    case  3: case  4: case  5: case 16: case 28: case 40: case 48: case 49: case 50:
    case 10: case 22: case 34:
      return 2;
      break;
    case  0: case  1: case  2: case 17: case 18: case 19: case 20: case 29: case 30:
    case 31: case 32: case 41: case 42: case 43: case 44: case 51: case 52: case 53: 
    case  9: case 21: case 33:     
      return 1;
      break;
    default:
      cout << "Error in search_layer_BF()";
      return -1; // error
      break;
  }
}

// Search in which layer from LEFT to RIGHT of the cube is element "a"  
int RubiksCube::search_layer_LR(int a) {

  int    pos  = search_pos(a);
  string face = search_face(pos);

  switch (search_pos(a)) {
    case  0: case  3: case  6: case  9: case 10: case 11: case 12: case 21: case 22:
    case 23: case 24: case 33: case 34: case 35: case 36: case 45: case 48: case 51:
    case 20: case 32: case 44:
      return 1;
      break;
    case  1: case  4: case  7: case 13: case 25: case 37: case 46: case 49: case 52:
    case 19: case 31: case 43:
      return 2;
      break;
    case  2: case  5: case  8: case 47: case 50: case 53: case 14: case 15: case 16:
    case 17: case 18: case 26: case 27: case 28: case 29: case 30: case 38: case 39: 
    case 40: case 41: case 42:     
      return 3;
      break;
    default:
      cout << "Error in search_layer_LR()";
      return -1; // error
      break;
  }
}

// Bring angle piece of element "a" to the down layer
void RubiksCube::bring_down_angle(int a) {
    
  int l_BF = search_layer_BF(a);
  int l_LR = search_layer_LR(a);

  if (l_BF == 1 && l_LR == 1) { this -> move("l d L"); }
  if (l_BF == 1 && l_LR == 3) { this -> move("b d B"); }
  if (l_BF == 3 && l_LR == 1) { this -> move("f d F"); }
  if (l_BF == 3 && l_LR == 3) { this -> move("r d R"); }
}

// Bring edge piece of element "a" to the down layer
void RubiksCube::bring_down_edge(int a) {
  
  int l_BF = search_layer_BF(a);
  int l_LR = search_layer_LR(a);

  if (l_BF == 1 && l_LR == 1) { this -> move("l D D f d F D D L"); }
  if (l_BF == 1 && l_LR == 3) { this -> move("b D D l d L D D B"); }
  if (l_BF == 3 && l_LR == 3) { this -> move("r D D b d B D D R"); }
  if (l_BF == 3 && l_LR == 1) { this -> move("f D D r d R D D F"); }
}

// Inverse of a move
string RubiksCube::inv(string move) {
  char in_char = move[0];
  if (isupper(in_char)) {in_char=tolower(in_char);}
  else {(move=toupper(in_char));}
  string out_str;
  out_str.push_back(in_char);
  return out_str;
}

// Solve the cube
bool RubiksCube::solve(int & mc , string & ms) {

  move_seq.clear(); // Clearing the sequernce of move variable
  move_count = 0;   // Resetting the move counter
 
  // Actually solving the cube -> reordering the state vector
  white_cross();
  white_angles();
  middle_edges();
  yellow_cross();
  yellow_angles();

  mc = move_count;
  ms = move_seq;

  move_seq.clear(); // Clearing the sequernce of move variable
  move_count = 0;   // Resetting the move counter

  // Checking if cube is solved
  if (std::is_sorted(state.begin(), state.end())) {
    return true;
  } else {
    return false;
  }
}

// Solve the white cross
void RubiksCube::white_cross() {

  int max_iter; // Maximum number of iteration, defined to stop the 
                // algorithm in case of infinite loop failure

  // === Piece 1-19 ====
  max_iter = 0;
  while (state[1] != 1 && max_iter < 20) {
    string face_to_move;
    switch ( mymap_si.find(search_face(1))->second ) {
      case 5: // element 1 is on the upper face
        this -> move("U");
        break;
      case 11: // element 1 is on the down face
        face_to_move = search_face(19);
        this -> move(face_to_move + face_to_move);
        break;
      case 1: case 3: case 7: case 9: // element 1 is on in the other faces
        if (search_layer(1) == 2)                              { this -> move(search_face(19)); }
        else if (search_layer(1) == 3 || search_layer(1) == 1) { this -> move(search_face(1)); }
        break;
    }
    max_iter++;
  }

  // === Piece 3-10 ====
  max_iter = 0;
  while (state[3] != 3 && max_iter < 20) {
    switch ( mymap_si.find(search_face(3))->second ) {
      case 5: // element 3 is on the upper face
        this -> move("B");
        while (state[3] != 3 ) this -> move("U");
        this -> move("b");
        break;
      case 11: // element 3 is on the down face
        while (search_face(10) != "L" ) this -> move("D");
        this -> move("L L");
        break;
      case 1: case 3: case 7: case 9: // element 3 is in the other faces
        if (search_layer(3) == 1) {
          if      (search_face(3) == "L") { this -> move("L"); }
          else if (search_face(3) == "R") { this -> move("r"); }
          else if (search_face(3) == "F") { this -> move("F"); }
        }
        else if (search_layer(3) == 2) {
          if (search_face(10) != "B") { this -> move(search_face(10)); }
          else                        { this -> move(search_face(3)); }
        }
        else if (search_layer(3) == 3) {
          if (search_face(3) != "B") { this -> move(search_face(3)); }
          else                       { this -> move("D"); }
        }
        break;
    }
    max_iter++;
  }

  // === Piece 5-16 ====
  max_iter = 0;
  while (state[5] != 5 && max_iter < 20) {
    switch ( mymap_si.find(search_face(5))->second ) {
      case 5: // element 5 is on the upper face
        this -> move("F U f u");
        break;
      case 11: // element 5 is on the down face
        while (search_face(16) != "R" ) this -> move("D");
        this -> move("R R");
        break;        
      case 1: case 3: case 7: case 9: // element 5 is in the other faces
        if (search_layer(5) == 1) {
          if (search_face(5) == "F") {
            this -> move("F R");
          }
          else if (search_face(5) == "R") {
            this -> move("r U f u");
          }
        }
        else if (search_layer(5) == 2) {
          int coun = 0;
          int align_piece = state[13];
          while ( search_face(5) != search_face(align_piece) ) {
            this -> move("U");
            coun++;
          }
          this -> move(search_face(5));
          for (int i = 0; i < coun; i++) this -> move("u");
        }
        else if (search_layer(5) == 3) {
          while (search_face(5) != "F") this -> move("D");
          this -> move("f R");
        }        
        break;
    }
    max_iter++;
  }

  // === Piece 7-13 ====
  max_iter = 0;
  while (state[7] != 7 && max_iter < 20) {
    switch ( mymap_si.find(search_face(7))->second ) {
      case 11: // element 7 is on the down face
        while ( search_face(13) != "F" ) this -> move("D");
        this -> move("F F");
        break;        
      case 1: case 3: case 7: case 9: // element 7 is in the other faces
        if (search_layer(7) == 1) {
          this -> move("F u R U");
        }
        else if (search_layer(7) == 2) {
          int coun = 0;
          int align_piece = state[13];
          while ( search_face(7) != search_face(align_piece) ){
            this -> move("U");
            coun++;
          }
          this -> move(search_face(7));
          for (int i = 0; i < coun; i++) this -> move("u");
        }
        else if (search_layer(7) == 3) {
          while (search_face(7) != "F") this -> move("D");
          this -> move("f u R U");
        }                
        break;
    }
    max_iter++;
  }
  
}

// Solve the white angles
void RubiksCube::white_angles() {
  vector<int> angles = {0, 2, 8, 6};

  // Iterate through elements 0, 2, 8, 6
  for (int i = 0; i < 4; i++) {
    int a = angles[i];
    int f1, f2;

    if      (a == 0) {f1 = 20; f2 = 17; }
    else if (a == 2) {f1 = 17; f2 = 14; } 
    else if (a == 8) {f1 = 14; f2 = 11; } 
    else if (a == 6) {f1 = 11; f2 = 20; } 

    string str_f1 = search_face(state[f1]);
    string str_f2 = search_face(state[f2]);
    
    int desired_l_BF = search_layer_BF(state[a]);
    int desired_l_LR = search_layer_LR(state[a]);
    
    int max_iter = 0;

    while (state[a] != a && max_iter < 5) {
      int l = search_layer(a);

      // Moving the angle down to the third layer
      if (l == 1) {
        bring_down_angle(a);
      }

      while ( (search_layer_BF(a) != desired_l_BF) || (search_layer_LR(a) != desired_l_LR) ) {
        this -> move("D");
      }

      if (search_face(a) == "D") {
        this -> move(str_f1 + str_f2 + "D D" + inv(str_f2) + inv(str_f1));
      } 
      else if (search_face(a) == str_f1) {
        this -> move(str_f1 + "D" + inv(str_f1));
      }
      else {
        this -> move("D" + str_f1 + "d" + inv(str_f1));
      }
      max_iter++;
    }
  }
}

// Solve middle edges
void RubiksCube::middle_edges() {
  
  // Iterate through the four edges pieces "21-32", "30-29", "27-26", "24-23"
  vector<int> edges = {21, 30, 27, 24};
  for (int i = 0; i < 4; i++) {
    
    int a = edges[i]; // element a
    int f1, f2;

    // Faces of interest to move middle edges:
    if      (a == 21) { f2 = 32; }
    else if (a == 30) { f2 = 29; } 
    else if (a == 27) { f2 = 26; } 
    else if (a == 24) { f2 = 23; }
    string ref_f1 = search_face(state[a]);
    string ref_f2 = search_face(state[f2]);
    
    int max_iter = 0;
    while (state[a] != a && max_iter < 10) {

      // Moving the edge down to the third layer (down layer)
      if (search_layer(a) == 2) {
        bring_down_edge(a);
      }

      while ( (search_face(a) != ref_f1  ) && (search_face(f2) !=  ref_f2 ) ) {
        this -> move("D");
      }

      if      ( search_face( a) == ref_f1 ) { this -> move("D" + ref_f2 + "d" + inv(ref_f2) + "d" + inv(ref_f1) + "D" + ref_f1); } 
      else if ( search_face(f2) == ref_f2 ) { this -> move("d" + inv(ref_f1) + "D" + ref_f1 + "D" + ref_f2 + "d" + inv(ref_f2)); }
      max_iter++;
    } 
  }
}

// Solve the yellow cross
void RubiksCube::yellow_cross() {

  // Edge pieces to move: 46-37 | 48-34 | 50-40 | 52-43
  string f46 = search_face(46);
  string f48 = search_face(48);
  string f50 = search_face(50);
  string f52 = search_face(52);

  // Moving all the yellow edges elements to the down face "D"
  if (f46 != "D" || f48 != "D" || f50 != "D" || f52 != "D" ) {
    
    // No yellow elements on D face
    if ( f46 != "D" && f48 != "D" && f50 != "D" && f52 != "D" ){ 
      // This move turns all edge pieces that are on D face
      this -> move("F L d l F L d l D D L D l f L D l f");
    }
    // Two aligned yellow edge-elements on positions 46-52 on D face  
    else if ( ( state[46] == 46 || state[46] == 48 || state[46] == 50 || state[46] == 52 ) &&
              ( state[52] == 46 || state[52] == 48 || state[52] == 50 || state[52] == 52 )    ) {
      this -> move("D");
      this -> move("F L D l d f");
    }
    // Two aligned yellow edge-elements on positions 48-50 on D face  
    else if ( ( state[48] == 46 || state[48] == 48 || state[48] == 50 || state[48] == 52 ) &&
              ( state[50] == 46 || state[50] == 48 || state[50] == 50 || state[50] == 52 )    ) {
      this -> move("F L D l d f");
    }
    // Two yellow edge-elements in positions 46-50 on D face
    else if ( ( state[46] == 46 || state[46] == 48 || state[46] == 50 || state[46] == 52 ) &&
              ( state[50] == 46 || state[50] == 48 || state[50] == 50 || state[50] == 52 )    ) {
      this -> move("L D B d b l");
    }
    // Two yellow edge-elements in positions 50-52 on D face
    else if ( ( state[50] == 46 || state[50] == 48 || state[50] == 50 || state[50] == 52 ) &&
              ( state[52] == 46 || state[52] == 48 || state[52] == 50 || state[52] == 52 )    ) {
      this -> move("d");
      this -> move("L D B d b l");
    }
    // Two yellow edge-elements in positions 52-48 on D face
    else if ( ( state[52] == 46 || state[52] == 48 || state[52] == 50 || state[52] == 52 ) &&
              ( state[48] == 46 || state[48] == 48 || state[48] == 50 || state[48] == 52 )    ) {
      this -> move("D D");
      this -> move("L D B d b l");
    }
    // Two yellow edge-elements in positions 48-46 on D face
    else if ( ( state[48] == 46 || state[48] == 48 || state[48] == 50 || state[48] == 52 ) && 
              ( state[46] == 46 || state[46] == 48 || state[46] == 50 || state[46] == 52 )    ) {
      this -> move("D");
      this -> move("L D B d b l");
    }
  }
  
  // Aligning the elment 37 to face F
  while (search_face(37) != "F") { this -> move("D"); }
  
  // Reordering the yellow edge-elements previously turn to down face
  if ( state[50] == 50 && state[52] != 52 && state[48] != 48 ) { // 52 and 48 not in position
    this -> move("R D r D R D D r D");
  }
  else if ( state[52] == 52 && state[50] != 50 && state[48] != 48 ) { // 48 and 50 not in position
    this -> move("D B D b D B D D b D F D f D F D D f d");
  }
  else if ( state[48] == 48 && state[52] != 52 && state[50] != 50 ) { // 50 and 52 not in position
    this -> move("F D f D F D D f D");
  } 
  else if ( state[48] != 48 && state[52] != 52 && state[50] != 50 ) { // 48 and 50 and 52 not in position
    if ( state[50] == 52 && state[48] == 50 && state[52] == 48 ) {
      this -> move("D D F D f D F D D f");
    }
    else if ( state[50] == 48 && state[48] == 52 && state[52] == 50 ) {
      this -> move("D F D f D F D D f d");
    }
  }
} 

// Solve the yellow angles
void RubiksCube::yellow_angles() {

  // Angle pieces to move: 45-35-36 | 47-38-39 | 53-41-42 | 51-33-44

  // Case 1: no angle piece is in the correct position
  if ( (search_layer_BF(45) != 3 || search_layer_LR(45) != 1) &&
       (search_layer_BF(47) != 3 || search_layer_LR(47) != 3) &&
       (search_layer_BF(53) != 1 || search_layer_LR(53) != 3) &&
       (search_layer_BF(51) != 1 || search_layer_LR(51) != 1)    ) {
    this -> move("D F d b D f d B");
  }

  // Case 2: one angle piece is in the correct position
  if ( ( search_layer_BF(45) == 3 && search_layer_LR(45) == 1 ) && ( search_layer_BF(47) != 3 || search_layer_LR(47) != 3 ) ) {
    while (search_layer_BF(47) != 3 || search_layer_LR(47) != 3) {
      this -> move("D L d r D l d R");
    }
  }
  else if ( ( search_layer_BF(47) == 3 && search_layer_LR(47) == 3 ) && ( search_layer_BF(53) != 1 || search_layer_LR(53) != 3 ) ) {
    while (search_layer_BF(53) != 1 || search_layer_LR(53) != 3) {
      this -> move("D F d b D f d B");
    } 
  }
  else if ( ( search_layer_BF(53) == 1 && search_layer_LR(53) == 3 ) && ( search_layer_BF(51) != 1 || search_layer_LR(51) != 1 ) ) {
    while (search_layer_BF(51) != 1 || search_layer_LR(51) != 1) {
      this -> move("D R d l D r d L");
    } 
  }
  else if ( ( search_layer_BF(51) == 1 && search_layer_LR(51) == 1 ) && ( search_layer_BF(45) != 3 || search_layer_LR(45) != 1 ) ) {
    while (search_layer_BF(45) != 3 || search_layer_LR(45) != 1) {
      this -> move("D B d f D b d F");
    } 
  }

  // Case 3: all angle pieces are in the correct position, we have just to rotate them in place
  while ( search_face(45) != "D" ) { this -> move("l U L u l U L u"); }
  this -> move("d");
  while ( search_face(47) != "D" ) { this -> move("l U L u l U L u"); }
  this -> move("d");
  while ( search_face(53) != "D" ) { this -> move("l U L u l U L u"); }
  this -> move("d");
  while ( search_face(51) != "D" ) { this -> move("l U L u l U L u"); }
  this -> move("d");

} 

// Permutation of a move
void RubiksCube::permut(int a, int b, int c, int d) {
  int tmp = state[a];
  state[a] = state[b];
  state[b] = state[c];
  state[c] = state[d];
  state[d] = tmp;
}

// Move a face
void RubiksCube::single_move(string which_face) {
  switch ( mymap_si.find(which_face)->second ) {
    case 1: // F
      permut(36,38,14,12);
      permut(24,37,26,13);
      permut(6,35,47,15);
      permut(7,23,46,27);
      permut(8,11,45,39);
      break;
    case 2: // f
      permut(12,14,38,36);
      permut(13,26,37,24);
      permut(15,47,35,6);
      permut(27,46,23,7);
      permut(39,45,11,8);
      break;
    case 3: // R
      permut(39,41,17,15);
      permut(16,27,40,29);
      permut(2,14,47,42);
      permut(5,26,50,30);
      permut(8,38,53,18);
      break;
    case 4: // r      
      permut(15,17,41,39);
      permut(29,40,27,16);
      permut(42,47,14,2);
      permut(30,50,26,5);
      permut(18,53,38,8);  
      break;
    case 5: // U
      permut(0,6,8,2);
      permut(1,3,7,5);
      permut(9,12,15,18);
      permut(10,13,16,19);
      permut(11,14,17,20);
      break;
    case 6: // u
      permut(2,8,6,0);
      permut(5,7,3,1);
      permut(18,15,12,9);
      permut(19,16,13,10);
      permut(20,17,14,11);
      break; 
    case 7: // B
      permut(42,44,20,18);
      permut(19,30,43,32);
      permut(0,17,53,33);
      permut(1,29,52,21);
      permut(2,41,51,9);
      break;
    case 8: // b
      permut(18,20,44,42);
      permut(32,43,30,19);
      permut(33,53,17,0);
      permut(21,52,29,1);
      permut(9,51,41,2);
      break;
    case 9: // L
      permut(9,33,35,11);
      permut(10,21,34,23);
      permut(45,12,0,44);
      permut(32,48,24,3);
      permut(20,51,36,6);
      break;
    case 10: // l
      permut(11,35,33,9);
      permut(23,34,21,10);
      permut(44,0,12,45);
      permut(3,24,48,32);
      permut(6,36,51,20);
      break;
    case 11: // D
      permut(47,45,51,53);
      permut(46,48,52,50);
      permut(42,39,36,33);
      permut(43,40,37,34);
      permut(44,41,38,35);
      break;
    case 12: // d
      permut(53,51,45,47);
      permut(50,52,48,46);
      permut(33,36,39,42);
      permut(34,37,40,43);
      permut(35,38,41,44);
      break;
    default: // error
      cout << "Unknown move!\n";
      break;
  }
  move_count++;
  move_seq.append(which_face);
}

// Print the state
void RubiksCube::print() {
  cout << "\n";

  cout << "\t\t\t" << state[0] << "\t" << state[1] << "\t" << state[2] << "\t" << "\t\t\t" << "\t\t\t" << "\n";
  cout << "\t\t\t" << state[3] << "\t" << state[4] << "\t" << state[5] << "\t" << "\t\t\t" << "\t\t\t" << "\n";
  cout << "\t\t\t" << state[6] << "\t" << state[7] << "\t" << state[8] << "\t" << "\t\t\t" << "\t\t\t" << "\n";

  cout <<  state[9] << "\t" << state[10] << "\t" << state[11] << "\t" << state[12] << "\t" << state[13] << "\t" << state[14] << "\t" << state[15] << "\t" << state[16] << "\t" << state[17] << "\t" << state[18] << "\t" << state[19] << "\t" << state[20] << "\t"<<"\n";
  cout << state[21] << "\t" << state[22] << "\t" << state[23] << "\t" << state[24] << "\t" << state[25] << "\t" << state[26] << "\t" << state[27] << "\t" << state[28] << "\t" << state[29] << "\t" << state[30] << "\t" << state[31] << "\t" << state[32] << "\t"<<"\n";
  cout << state[33] << "\t" << state[34] << "\t" << state[35] << "\t" << state[36] << "\t" << state[37] << "\t" << state[38] << "\t" << state[39] << "\t" << state[40] << "\t" << state[41] << "\t" << state[42] << "\t" << state[43] << "\t" << state[44] << "\t"<<"\n";

  cout << "\t\t\t" << state[45] << "\t" << state[46] << "\t" << state[47] << "\t" << "\t\t\t" << "\t\t\t" << "\n";
  cout << "\t\t\t" << state[48] << "\t" << state[49] << "\t" << state[50] << "\t" << "\t\t\t" << "\t\t\t" << "\n";
  cout << "\t\t\t" << state[51] << "\t" << state[52] << "\t" << state[53] << "\t" << "\t\t\t" << "\t\t\t" << "\n";
  
  cout << "\n";
}

// Main method
void RubiksCube::is_this_water() {
  cout << "\nYou just asked if the class is water... the answer is NO!\n";
}