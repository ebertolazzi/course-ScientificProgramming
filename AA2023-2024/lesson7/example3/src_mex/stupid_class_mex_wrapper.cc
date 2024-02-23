/****************************************************************************\
  Copyright (c) Enrico Bertolazzi 2016
  All Rights Reserved.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the file license.txt for more details.
\****************************************************************************/

#include "mex_utils.hh"
#include "stupid_class.hh"

#include <map>
#include <exception>

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
"stupid_class_mex_wrapper: Do something\n" \
"\n" \
"USAGE:\n" \
"  res = stupid_class_mex_wrapper( 'action', ... );\n" \
"======================================================================\n"

namespace a_namespace_used {


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  static
  void
  do_new( int nlhs, mxArray       *plhs[],
          int nrhs, mxArray const *[] ) {

    #define MEX_ERROR_MESSAGE_1 "stupid_class_mex_wrapper( 'new' )"
    #define CMD MEX_ERROR_MESSAGE_1

    UTILS_MEX_ASSERT( nrhs == 1, CMD ": expected 1 inputs, nrhs = {}\n", nrhs );
    UTILS_MEX_ASSERT( nlhs == 1, CMD ": expected 1 output, nlhs = {}\n", nlhs );

    arg_out_0 = Utils::mex_convert_ptr_to_mx<stupid_class>( new stupid_class() );

    #undef CMD
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  static
  void
  do_delete( int nlhs, mxArray       *[],
             int nrhs, mxArray const *prhs[] ) {

    #define MEX_ERROR_MESSAGE_2 "stupid_class_mex_wrapper( 'delete', OBJ ): "
    #define CMD MEX_ERROR_MESSAGE_2

    UTILS_MEX_ASSERT( nrhs == 2, CMD ": expected 2 inputs, nrhs = {}\n", nrhs );
    UTILS_MEX_ASSERT( nlhs == 0, CMD ": expected 0 output, nlhs = {}\n", nlhs );

    // Destroy the C++ object
    Utils::mex_destroy_object<stupid_class>(arg_in_1);

    #undef CMD
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  static
  void
  do_change_status( int nlhs, mxArray       *[],
                    int nrhs, mxArray const *prhs[] ) {

    #define MEX_ERROR_MESSAGE_3 "stupid_class_mex_wrapper( 'change_status', OBJ, str )"
    #define CMD MEX_ERROR_MESSAGE_3

    UTILS_MEX_ASSERT( nrhs == 3, CMD ": expected 3 inputs, nrhs = {}\n", nrhs );
    UTILS_MEX_ASSERT( nlhs == 0, CMD ": expected 0 output, nlhs = {}\n", nlhs );

    char new_status_c[256];
    mxGetString( arg_in_2, new_status_c, 256 );
    std::string new_status{new_status_c};

    stupid_class * ptr = Utils::mex_convert_mx_to_ptr<stupid_class>( arg_in_1 );

    ptr->change_status( new_status );

    #undef CMD
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  static
  void
  do_print_status( int nlhs, mxArray       *plhs[],
                   int nrhs, mxArray const *prhs[] ) {

    #define MEX_ERROR_MESSAGE_4 "stupid_class_mex_wrapper( 'print_status', OBJ )"
    #define CMD MEX_ERROR_MESSAGE_4

    UTILS_MEX_ASSERT( nrhs == 2, CMD ": expected 2 inputs, nrhs = {}\n", nrhs );
    UTILS_MEX_ASSERT( nlhs == 1, CMD ": expected 1 output, nlhs = {}\n", nlhs );

    stupid_class * ptr = Utils::mex_convert_mx_to_ptr<stupid_class>( arg_in_1 );

    std::string msg = ptr->print_status();

    arg_out_0 = mxCreateString(msg.c_str());

    #undef CMD
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  typedef void (*DO_CMD)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

  static std::map<std::string,DO_CMD> cmd_to_fun = {
    {"new",do_new},
    {"delete",do_delete},
    {"change_status",do_change_status},
    {"print_status",do_print_status}
  };

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  extern "C"
  void
  mexFunction( int nlhs, mxArray       *plhs[],
               int nrhs, mxArray const *prhs[] ) {

    char cmd[256];

    // the first argument must be a string
    if ( nrhs == 0 ) { mexErrMsgTxt("string expected"); return; }

    try {
      UTILS_MEX_ASSERT0( mxIsChar(arg_in_0), "First argument must be a string" );
      mxGetString( arg_in_0, cmd, 256 );
      cmd_to_fun.at(cmd)( nlhs, plhs, nrhs, prhs );
    } catch ( std::exception const & e ) {
      mexErrMsgTxt( fmt::format( "stupid_class_mex_wrapper Error: {}", e.what() ).c_str() );
    } catch (...) {
      mexErrMsgTxt("stupid_class_mex_wrapper failed\n");
    }

  }

}
