/****************************************************************************\
  Copyright (c) Enrico Bertolazzi 2016
  All Rights Reserved.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the file license.txt for more details.
\****************************************************************************/

#include "mex_utils.hh"
#include <cmath>

#define MEX_ERROR_MESSAGE \
"=====================================================================================\n" \
"mex_CubicSegment2: XXX\n" \
"\n" \
"USAGE:\n" \
"  - Constructors:\n" \
"    OBJ = mex_CubicSegment2( 'new' );\n" \
"\n" \
"    On output:\n" \
"    OBJ = pointer to the internal object\n" \
"\n" \
"    res = mex_CubicSegment2( 'eval', OBJ, t );\n" \
"\n" \
"=====================================================================================\n"

using namespace std;

#include <Eigen/Dense>

/*\
 |  ____    _  _____  _
 | |  _ \  / \|_   _|/ \
 | | | | |/ _ \ | | / _ \
 | | |_| / ___ \| |/ ___ \
 | |____/_/   \_\_/_/   \_\
 |
\*/

typedef double real_type;
typedef Eigen::Matrix<real_type,Eigen::Dynamic,1> vec;

class CubicSegment2 {
  int dim;
  vec P0, P1, T0, T1;
  mutable vec tmp;
public:

  CubicSegment2() {}
  ~CubicSegment2() {}

  void
  build( int sz,
         real_type const p0[],
         real_type const p1[],
         real_type const t0[],
         real_type const t1[] ) {
    this->dim = sz;
    this->P0.resize(sz);
    this->P1.resize(sz);
    this->T0.resize(sz);
    this->T1.resize(sz);
    this->tmp.resize(sz);
    for ( int i = 0; i < sz; ++i ) {
      this->P0(i) = p0[i];
      this->P1(i) = p1[i];
      this->T0(i) = t0[i];
      this->T1(i) = t1[i];
    }
  }

  void
  base( real_type   t,
        real_type & h0,
        real_type & h1,
        real_type & l0,
        real_type & l1 ) const {
    real_type bt  = 1-t;
    real_type t2  = t*t;
    real_type bt2 = bt*bt;
    h0 = (1+2*t)*bt2;
    h1 = (1+2*bt)*t2;
    l0 = t*bt2;
    l1 = -t2*bt;
  }

  void
  base_D( real_type   t,
          real_type & h0,
          real_type & h1,
          real_type & l0,
          real_type & l1 ) const {
    real_type bt = 1-t;
    h0 = -6*bt*t;
    h1 = 6*bt*t;
    l0 = bt*(1-3*t);
    l1 = t*(1-3*bt);
  }

  void
  base_DD( real_type   t,
           real_type & h0,
           real_type & h1,
           real_type & l0,
           real_type & l1 ) const {
    h0 = 12*t-6;
    h1 = 6-12*t;
    l0 = 6*t-4;
    l1 = 6*t-2;
  }

  void
  base_DDD( real_type   t,
            real_type & h0,
            real_type & h1,
            real_type & l0,
            real_type & l1 ) const {
    h0 = 12;
    h1 = -12;
    l0 = 6;
    l1 = 6;
  }

  int
  get_dim() const
  { return dim; }

  void
  eval( int sw,
        real_type const t[],
        real_type       res[] ) const {
    real_type h0, h1, l0, l1;
    int kk = 0;
    for ( int i = 0; i < sw; ++i ) {
      this->base( t[i], h0, h1, l0, l1 );
      tmp = h0*this->P0 + h1*this->P1 + l0*this->T0 + l1*this->T1;
      for ( int j = 0 ; j < dim; ++j )
        res[kk++] = tmp[j];
    }
  }
};

static
void
DATA_NEW( mxArray * & mx_id ) {
  CubicSegment2 * ptr = new CubicSegment2();
  mx_id = convertPtr2Mat<CubicSegment2>(ptr);
}

static
inline
CubicSegment2 *
DATA_GET( mxArray const * & mx_id ) {
  return convertMat2Ptr<CubicSegment2>(mx_id);
}

/*\
 *                      _____                 _   _
 *  _ __ ___   _____  _|  ___|   _ _ __   ___| |_(_) ___  _ __
 * | '_ ` _ \ / _ \ \/ / |_ | | | | '_ \ / __| __| |/ _ \| '_ \
 * | | | | | |  __/>  <|  _|| |_| | | | | (__| |_| | (_) | | | |
 * |_| |_| |_|\___/_/\_\_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|
 *
\*/

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_new( int nlhs, mxArray       *plhs[],
        int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('new'): "
  MEX_ASSERT( nrhs == 1, CMD "expected 1 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs );
  #undef CMD

  DATA_NEW( arg_out_0 );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_delete( int nlhs, mxArray       *plhs[],
           int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('delete',OBJ): "
  MEX_ASSERT( nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 0, CMD "expected NO output, nlhs = " << nlhs );
  #undef CMD

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ
  if ( ptr != nullptr ) delete ptr;

}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_base( int nlhs, mxArray       *plhs[],
         int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('base',OBJ,t): "
  MEX_ASSERT( nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 4, CMD "expected 4 output, nlhs = " << nlhs );

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ

  mwSize sz ;
  real_type const * tt = getVectorPointer(
    arg_in_2, sz, CMD "t expected be a real vector"
  );

  real_type * h0 = createMatrixValue( arg_out_0, sz, 1 );
  real_type * h1 = createMatrixValue( arg_out_1, sz, 1 );
  real_type * l0 = createMatrixValue( arg_out_2, sz, 1 );
  real_type * l1 = createMatrixValue( arg_out_3, sz, 1 );

  for ( mwSize i = 0; i < sz; ++i )
    ptr->base( tt[i], h0[i], h1[i], l0[i], l1[i] );

  #undef CMD
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_base_D( int nlhs, mxArray       *plhs[],
           int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('base_D',OBJ,t): "
  MEX_ASSERT( nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 4, CMD "expected 4 output, nlhs = " << nlhs );

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ

  mwSize sz ;
  real_type const * tt = getVectorPointer(
    arg_in_2, sz, CMD "t expected be a real vector"
  );

  real_type * h0 = createMatrixValue( arg_out_0, sz, 1 );
  real_type * h1 = createMatrixValue( arg_out_1, sz, 1 );
  real_type * l0 = createMatrixValue( arg_out_2, sz, 1 );
  real_type * l1 = createMatrixValue( arg_out_3, sz, 1 );

  for ( mwSize i = 0; i < sz; ++i )
    ptr->base_D( tt[i], h0[i], h1[i], l0[i], l1[i] );

  #undef CMD
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_base_DD( int nlhs, mxArray       *plhs[],
            int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('base_DD',OBJ,t): "
  MEX_ASSERT( nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 4, CMD "expected 4 output, nlhs = " << nlhs );

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ

  mwSize sz ;
  real_type const * tt = getVectorPointer(
    arg_in_2, sz, CMD "t expected be a real vector"
  );

  real_type * h0 = createMatrixValue( arg_out_0, sz, 1 );
  real_type * h1 = createMatrixValue( arg_out_1, sz, 1 );
  real_type * l0 = createMatrixValue( arg_out_2, sz, 1 );
  real_type * l1 = createMatrixValue( arg_out_3, sz, 1 );

  for ( mwSize i = 0; i < sz; ++i )
    ptr->base_DD( tt[i], h0[i], h1[i], l0[i], l1[i] );

  #undef CMD
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_base_DDD( int nlhs, mxArray       *plhs[],
             int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('base_DDD',OBJ,t): "
  MEX_ASSERT( nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 4, CMD "expected 4 output, nlhs = " << nlhs );

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ

  mwSize sz ;
  real_type const * tt = getVectorPointer(
    arg_in_2, sz, CMD "t expected be a real vector"
  );

  real_type * h0 = createMatrixValue( arg_out_0, sz, 1 );
  real_type * h1 = createMatrixValue( arg_out_1, sz, 1 );
  real_type * l0 = createMatrixValue( arg_out_2, sz, 1 );
  real_type * l1 = createMatrixValue( arg_out_3, sz, 1 );

  for ( mwSize i = 0; i < sz; ++i )
    ptr->base_DDD( tt[i], h0[i], h1[i], l0[i], l1[i] );

  #undef CMD
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_build( int nlhs, mxArray       *plhs[],
          int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('build',OBJ,p0,p1,t0,t1): "
  MEX_ASSERT( nrhs == 6, CMD "expected 6 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 0, CMD "expected NO output, nlhs = " << nlhs );

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ

  mwSize sz0, sz1, sz2, sz3;
  real_type const * p0 = getVectorPointer(
    arg_in_2, sz0, CMD "p0 expected be a real vector"
  );
  real_type const * p1 = getVectorPointer(
    arg_in_3, sz1, CMD "p1 expected be a real vector"
  );
  real_type const * t0 = getVectorPointer(
    arg_in_4, sz2, CMD "t0 expected be a real vector"
  );
  real_type const * t1 = getVectorPointer(
    arg_in_5, sz3, CMD "p0 expected be a real vector"
  );

  MEX_ASSERT( sz0 == sz1 && sz0 == sz2 && sz0 == sz3,
              CMD "bad dimension lenght(p0) = " << sz0 <<
              " lenght(p1) = " << sz1 <<
              " lenght(t0) = " << sz2 <<
              " lenght(t1) = " << sz3 );

  ptr->build( sz0, p0, p1, t0, t1 );

  #undef CMD
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

static
void
do_eval( int nlhs, mxArray       *plhs[],
         int nrhs, mxArray const *prhs[] ) {

  #define CMD "mex_CubicSegment2('eval',OBJ,t): "
  MEX_ASSERT( nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs );
  MEX_ASSERT( nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs );

  CubicSegment2 * ptr = DATA_GET( arg_in_1 ); // get OBJ

  mwSize sz;
  real_type const * t = getVectorPointer(
    arg_in_2, sz, CMD "t expected be a real vector"
  );

  mwSize dim = ptr->get_dim();
  real_type * res = createMatrixValue( arg_out_0, dim, sz );

  ptr->eval( sz, t, res );

  #undef CMD
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

/*\
  List of methods to be mapped
\*/
typedef enum {
  CMD_NEW,
  CMD_DELETE,
  CMD_BASE,
  CMD_BASE_D,
  CMD_BASE_DD,
  CMD_BASE_DDD,
  CMD_BUILD,
  CMD_EVAL
} CMD_LIST;

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

/*\
  Use MAP to connect mapped methods with strings
\*/

static map<string,unsigned> cmd_to_idx = {
  {"new",CMD_NEW},
  {"delete",CMD_DELETE},
  {"base",CMD_BASE},
  {"base_D",CMD_BASE_D},
  {"base_DD",CMD_BASE_DD},
  {"base_DDD",CMD_BASE_DDD},
  {"build",CMD_BUILD},
  {"eval",CMD_EVAL}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

extern "C"
void
mexFunction( int nlhs, mxArray       *plhs[],
             int nrhs, mxArray const *prhs[] ) {
  // the first argument must be a string
  if ( nrhs == 0 ) {
    mexErrMsgTxt(MEX_ERROR_MESSAGE);
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
    case CMD_BASE:
      do_base( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_BASE_D:
      do_base_D( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_BASE_DD:
      do_base_DD( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_BASE_DDD:
      do_base_DDD( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_BUILD:
      do_build( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_EVAL:
      do_eval( nlhs, plhs, nrhs, prhs );
      break;
    }
  } catch ( exception const & e ) {
    string err = mxArrayToString(arg_in_0);
    err += "\n";
    err += e.what();
    mexErrMsgTxt(err.c_str());
  } catch (...) {
    mexErrMsgTxt("CubicSegment2 failed, unknown error\n");
  }

}
