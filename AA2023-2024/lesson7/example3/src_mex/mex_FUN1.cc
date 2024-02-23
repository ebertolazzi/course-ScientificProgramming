/****************************************************************************\
  Copyright (c) Enrico Bertolazzi 2016
  All Rights Reserved.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the file license.txt for more details.
\****************************************************************************/

#include "mex_utils.hh"

#ifdef _MSC_VER
  #pragma comment(lib, "IPHLPAPI.lib")
  #pragma comment(lib, "ws2_32.lib")
  #pragma comment(lib, "Shlwapi.lib")
  #pragma comment(lib, "Advapi32.lib")
  #pragma comment(lib, "Shell32.lib")
  #pragma comment(lib, "kernel32.lib")
#endif

#define MEX_ERROR_MESSAGE \
"======================================================================\n" \
"\n" \
"FUN1: Do something\n" \
"\n" \
"USAGE:\n" \
"  res = FUN1( 'action', arg1, arg2 );\n" \
"======================================================================\n"

namespace a_namespace_used {

  extern "C"
  void
  mexFunction(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {

    if ( nrhs == 0 && nlhs == 0 ) {
      mexErrMsgTxt(MEX_ERROR_MESSAGE);
      return;
    }

    try {

      // must be 1 only input argument of type string
      UTILS_MEX_ASSERT( nrhs == 3, "FUN1 expected 3 input, found: {}\n", nrhs );


      // must be 1 only input argument of type string
      UTILS_MEX_ASSERT( nlhs == 1, "FUN1 expected 1 output, found: {}\n", nlhs );

      // prhs[0] == arg_in_0
      UTILS_MEX_ASSERT0( mxIsChar(arg_in_0), "First argument must be a string" );

      // read the argument form MATLAB
      char arg0_c[256];
      mxGetString( arg_in_0, arg0_c, 256 );
      std::string arg0{arg0_c};

      // prhs[1] == arg_in_1
      double arg1 = Utils::mex_get_scalar_value( arg_in_1, "Second argument must a scalar number" );

      // prhs[1] == arg_in_1
      double arg2 = Utils::mex_get_scalar_value( arg_in_2, "Third argument must a scalar number" );

      // possible actions
      // SUM
      // SUB
      // MUL
      // DIV
      // POW

      std::map<std::string,int> commands{
        {"SUM",0},
        {"SUB",1},
        {"MUL",2},
        {"DIV",3},
        {"POW",4}
      };

      double res{0};
      switch ( commands.at(arg0) ) {
      case 0: res = arg1+arg2; break;
      case 1: res = arg1-arg2; break;
      case 2: res = arg1*arg2; break;
      case 3: res = arg1/arg2; break;
      case 4: res = std::pow(arg1,arg2); break;
      }

      //std::string msg = fmt::format( "ARGUMENT PASSED = {}\n", arg0 );
      //mexPrintf("%s", msg.c_str());

      // store the results
      // plhs[0] == arg_out_0
      Utils::mex_set_scalar_value( arg_out_0, res );
    } catch ( std::exception const & e ) {
      mexErrMsgTxt( fmt::format( "FUN1 Error: {}", e.what() ).c_str() );
    } catch (...) {
  	  mexErrMsgTxt("FUN1 failed\n");
    }

  }

}
