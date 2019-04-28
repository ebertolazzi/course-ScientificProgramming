/* ======================================================================== *\
Mex file for RubiksCubeClass
Alessandro Antonucci and Davide Vignotto
University of Trento
\* ======================================================================== */

// Libraries
#include <vector>
#include <string> 
#include <map>

#include "mex_utils.hpp"
#include "RubiksCubeClass.hpp"

// Namespace
using namespace std;

/*==========================================================================*\
Mex Function
\*==========================================================================*/

static
void
DATA_NEW( mxArray * & mx_id ) {
  RubiksCube * ptr = new RubiksCube();
  mx_id = convertPtr2Mat<RubiksCube>(ptr);
}

static
inline
RubiksCube *
DATA_GET( mxArray const * & mx_id ) {
  return convertMat2Ptr<RubiksCube>(mx_id);
}

// Callback for methods

static
void
do_new( int nlhs, mxArray       *plhs[],
        int nrhs, mxArray const *prhs[] ) {

  DATA_NEW(arg_out_0); // get OBJ
}

static
void
do_delete( int nlhs, mxArray       *plhs[],
           int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ
  if ( ptr != nullptr ) delete ptr;
}

static
void
do_get_state( int nlhs, mxArray       *plhs[],
              int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ

  vector<int> act_state = ptr -> get_state();

   // output
  int * matlab_vector = createMatrixInt32( arg_out_0, 1 , act_state.size() );
  for (int i = 0; i < act_state.size(); i++) {
    matlab_vector[i] = act_state[i];
  }
}

static
void
do_rand_shuffle( int nlhs, mxArray       *plhs[],
                 int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ

  // arguments
  int64_t n_moves = getInt(arg_in_2 , "Error getInt in rand_shuffle");
  string move_seq;
  ptr -> rand_shuffle(n_moves,move_seq);

  // output
  setScalarString( arg_out_0 , move_seq);
}

static
void
do_move( int nlhs, mxArray       *plhs[],
         int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ

  // arguments
  std::string str = getString(arg_in_2, "Error getString in move");
  
  ptr -> move(str);
}

static
void
do_solve( int nlhs, mxArray       *plhs[],
          int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ
  
  int n_moves;
  string move_seq;
  
  bool solved = ptr -> solve(n_moves, move_seq);

  // outputs
  setScalarBool(   arg_out_0 , solved);
  setScalarInt(    arg_out_1 , n_moves);
  setScalarString( arg_out_2 , move_seq);
}

static
void
do_print( int nlhs, mxArray       *plhs[],
          int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ

  ptr -> print();
}

static
void
do_is_this_water( int nlhs, mxArray       *plhs[],
          int nrhs, mxArray const *prhs[] ) {

  RubiksCube *ptr = DATA_GET(arg_in_1); // get OBJ

  ptr -> is_this_water();
}

// List of methods to be mapped

typedef enum {
  CMD_NEW,
  CMD_DELETE,
  CMD_GET_STATE,
  CMD_RAND_SHUFFLE,
  CMD_MOVE,
  CMD_SOLVE,
  CMD_PRINT,
  CMD_IS_THIS_WATER
} CMD_LIST;

// Use MAP to connect mapped methods with strings

static map<string,unsigned> cmd_to_idx = {
  {"new",CMD_NEW},
  {"delete",CMD_DELETE},
  {"get_state",CMD_GET_STATE},
  {"rand_shuffle",CMD_RAND_SHUFFLE},
  {"move",CMD_MOVE},
  {"solve",CMD_SOLVE},
  {"print",CMD_PRINT},
  {"is_this_water",CMD_IS_THIS_WATER}
};

// MEX

extern "C"
void
mexFunction( int nlhs, mxArray       *plhs[],
             int nrhs, mxArray const *prhs[] ) {
  // the first argument must be a string
  if ( nrhs == 0 ) {
    mexErrMsgTxt("Erro: first argument must be a string!!");
    return;
  }

  try {

    MEX_ASSERT( mxIsChar(arg_in_0), "First argument must be a string" );
    string cmd = mxArrayToString(arg_in_0);

    switch ( cmd_to_idx.at(cmd) ) {
    case CMD_NEW:
      do_new( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_DELETE:
      do_delete( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_GET_STATE:
      do_get_state( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_RAND_SHUFFLE:
      do_rand_shuffle( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_MOVE:
      do_move( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_SOLVE:
      do_solve( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_PRINT:
      do_print( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_IS_THIS_WATER:
      do_is_this_water( nlhs, plhs, nrhs, prhs );
      break;
    }
  } catch ( exception const & e ) {
    string err = mxArrayToString(arg_in_0);
    err += "\n";
    err += e.what();
    mexErrMsgTxt(err.c_str());
  } catch (...) {
    mexErrMsgTxt("RubiksCubeClass failed, unknown error\n");
  }

}
