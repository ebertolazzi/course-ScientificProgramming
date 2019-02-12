/*
 Some experiments using Eigen3

 -I/usr/local/include/eigen3  to add search of headers for eigen3 library

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string> // C++ string
#include <exception>      // std::exception

// include headers for the Dense linear algebra of Eigen library
#include <Eigen/Dense>

using namespace std ;
//using namespace Eigen ;

int
main() {

  try {
    // define a matrix od double (d) of size 2x2
    // Matrix2d = Matrix<double,2,2>
    //Eigen::Matrix2d a;
    Eigen::Matrix<double,2,2> a;
    a(0,0) = 1;
    a(0,1) = 2;
    a(1,0) = 3;
    a(1,1) = 4;

    a << 1, 2,
         3, 4;
    
    // MatrixXd = Matrix<double,Dynamic,Dynamic>
    Eigen::MatrixXd b(2,2) ;
    b << 2, 3,
         1, 4;

    cout << "a + b =\n" << a + b << '\n' ;
    cout << "a - b =\n" << a - b << '\n' ;
    cout << "Doing a += b;" << '\n' ;
    a += b;
    cout << "Now a =\n" << a << '\n' ;
    // Vector3d = Matrix<double,3,1>
    Eigen::Vector3d v(1,2,3); // v << 1 << 2 << 3 ;
    Eigen::Vector3d w(1,0,0); // v << 1 << 0 << 0 ;
    cout << "-v + w - v =\n" << -v + w - v << '\n' ;
  }
  catch ( exception const & error ) {
    cerr << "Exception number " << error.what() << "\n"  ;
  }
  catch ( ... ) {
    cerr << "Exception found: Unknown error\n"  ;
  }
  cout << "END OF PROGRAM\n" ;

  return 0 ;
}

