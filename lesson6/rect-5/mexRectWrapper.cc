#include "mex_utils.hh"
#include "rect.hh"

#define MEX_ERROR_MESSAGE \
"MexRectWrapper error\n"


namespace GEOM {

  using std::string;

  void
  do_new(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {

    #define CMD "MexrectWrapper('new',[min_x,min_y,max_x,max_y]): "
    MEX_ASSERT( nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n' );
    MEX_ASSERT( nrhs == 1 || nrhs == 5, CMD "expected 1 or 5 input, nrhs = " << nrhs << '\n' );

    rect * ptr = nullptr;
    if ( nrhs == 5 ) {
      double min_x = getScalarValue( arg_in_1, "Error in reading min_x" );
      double min_y = getScalarValue( arg_in_2, "Error in reading min_y" );
      double max_x = getScalarValue( arg_in_3, "Error in reading max_x" );
      double max_y = getScalarValue( arg_in_4, "Error in reading max_y" );
      ptr = new rect( min_x, min_y, max_x, max_y );
    } else {
      ptr = new rect();
    }
    arg_out_0 = convertPtr2Mat<rect>(ptr);
    #undef CMD
  }

  void
  do_delete(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {

    #define CMD "MexrectWrapper('delete',self): "
    MEX_ASSERT( nlhs == 0, CMD "expected no output, nlhs = " << nlhs << '\n' );
    MEX_ASSERT( nrhs == 2, CMD "expected 2 input nrhs = " << nrhs << '\n' );

    rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
    delete ptr;

    #undef CMD
  }

  void
  do_copy(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD "MexrectWrapper('copy',self,obj): "
    MEX_ASSERT( nlhs == 0, CMD "expected no output, nlhs = " << nlhs << '\n' );
    MEX_ASSERT( nrhs == 3, CMD "expected 3 input nrhs = " << nrhs << '\n' );

    rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
    rect * ptr1 = convertMat2Ptr<rect>(arg_in_2);
    *ptr = *ptr1;

    #undef CMD
  }

  void
  do_translate(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD "MexrectWrapper('translate',self,dx,dy): "
    MEX_ASSERT( nlhs == 0, CMD "expected no output, nlhs = " << nlhs << '\n' );
    MEX_ASSERT( nrhs == 4, CMD "expected 4 input nrhs = " << nrhs << '\n' );

    rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
    double dx = getScalarValue( arg_in_2, "Error in reading dx" );
    double dy = getScalarValue( arg_in_3, "Error in reading dy" );
    ptr->translate( dx, dy );
    #undef CMD
  }

  void
  do_get_data(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD "MexrectWrapper('get_data',self): "
    MEX_ASSERT( nlhs == 4, CMD "expected 4 output, nlhs = " << nlhs << '\n' );
    MEX_ASSERT( nrhs == 2, CMD "expected 2 input nrhs = " << nrhs << '\n' );

    rect * ptr = convertMat2Ptr<rect>(arg_in_1);
    double min_x, min_y, max_x, max_y;
    ptr->get_data( min_x, min_y, max_x, max_y );
    setScalarValue( arg_out_0, min_x );
    setScalarValue( arg_out_1, min_y );
    setScalarValue( arg_out_2, max_x );
    setScalarValue( arg_out_3, max_y );
    #undef CMD
  }


  void
  do_collide(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD "MexrectWrapper('collide',self,obj): "
    MEX_ASSERT( nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n' );
    MEX_ASSERT( nrhs == 3, CMD "expected 3 input nrhs = " << nrhs << '\n' );

    rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
    rect * ptr1 = convertMat2Ptr<rect>(arg_in_2);
    bool ok = ptr->collide( * ptr1 );
    setScalarBool( arg_out_0, ok );
    #undef CMD
  }

  typedef void (*DO_CMD)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  static std::map<std::string,DO_CMD> cmd_to_fun = {
    {"new",do_new},
    {"delete",do_delete},
    {"copy",do_copy},
    {"translate",do_translate},
    {"collide",do_collide},
    {"get_data",do_get_data}
  };

  extern "C" // is a C function
  void
  mexFunction(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    // the first argument must be a string
    if ( nrhs == 0 ) {
      mexErrMsgTxt(MEX_ERROR_MESSAGE);
      return;
    }
    try {
      MEX_ASSERT( mxIsChar(arg_in_0), "First argument must be a string" );
      string cmd = mxArrayToString(arg_in_0);

      DO_CMD pfun = cmd_to_fun.at(cmd);
      pfun( nlhs, plhs, nrhs, prhs );
    } catch ( std::exception const & e ) {
      mexErrMsgTxt( ( string("MexRectWrapper Error: ")+e.what() ).c_str() );
    } catch (...) {
      mexErrMsgTxt("MexRectWrapper failed\n");
    }

  }

}
