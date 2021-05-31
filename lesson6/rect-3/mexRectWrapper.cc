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
  }

  void
  do_delete(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
    delete ptr;
  }

  void
  do_copy(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
   rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
   rect * ptr1 = convertMat2Ptr<rect>(arg_in_2);
   *ptr = *ptr1;
  }

  void
  do_translate(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
   rect * ptr  = convertMat2Ptr<rect>(arg_in_1);
   double dx = getScalarValue( arg_in_2, "Error in reading dx" );
   double dy = getScalarValue( arg_in_3, "Error in reading dy" );
   ptr->translate( dx, dy );
  }

  void
  do_get_data(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    rect * ptr = convertMat2Ptr<rect>(arg_in_1);
    double min_x, min_y, max_x, max_y;
    ptr->get_data( min_x, min_y, max_x, max_y );
    setScalarValue( arg_out_0, min_x );
    setScalarValue( arg_out_1, min_y );
    setScalarValue( arg_out_2, max_x );
    setScalarValue( arg_out_3, max_y );
  }

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

    MEX_ASSERT( mxIsChar(arg_in_0), "First argument must be a string" );
    string cmd = mxArrayToString(arg_in_0);

    if ( cmd == "new" ) {
      do_new( nlhs, plhs, nrhs, prhs );
    } else if ( cmd == "delete" ) {
      do_delete( nlhs, plhs, nrhs, prhs );
    } else if ( cmd == "copy" ) {
      do_copy( nlhs, plhs, nrhs, prhs );
    } else if ( cmd == "translate" ) {
      do_translate( nlhs, plhs, nrhs, prhs );
    } else if ( cmd == "get_data" ) {
      do_get_data( nlhs, plhs, nrhs, prhs );
    } else {
      std::cout << "MexRectWrapper(\"" << cmd << "\",...) unknown command\n";
    }

  }

}
