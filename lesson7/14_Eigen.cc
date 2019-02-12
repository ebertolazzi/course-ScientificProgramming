/*
 Some experiments using Eigen3

 -I/usr/local/include/eigen3  to add search of headers for eigen3 library


  Linear regression, bad way and good way.
  Using more Eigen3

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

template <typename T>
T
func( T x )
{ return 10*x-3 ; }

template <typename T>
void
generate_table( Eigen::Matrix<T,Eigen::Dynamic,1> & x,
                Eigen::Matrix<T,Eigen::Dynamic,1> & y,
                int                                 N ) {
  x.resize(N) ;               
  y.resize(N) ;
  
  for ( int i = 0 ; i < N ; ++i ) {
    T xx = ((rand() % 10000)-5000) * 0.001 ;
    T yy = func(xx) ;
    yy += ((rand() % 10000)-5000) * 0.0001 ;
    x(i) = xx ;
    y(i) = yy ;
  }

}

typedef double valueType ;

int
main() {

  try {
    int N = 1000000 ;
    Eigen::Matrix<double,Eigen::Dynamic,1> x, y ;
    generate_table( x, y, N ) ;
 
    // define a matrix od double (d) of size 2x2
    // Matrix2d = Matrix<double,2,2>
    Eigen::Matrix2d A ;
    Eigen::Vector2d b, sol ;
    
    valueType tmp = x.sum() ;
    A << x.dot(x), tmp,
         tmp,       N ;

    b << x.dot(y), y.sum() ;

    // use Cholewsky decomposition
    Eigen::LLT<Eigen::Matrix2d> lltOfA(A) ;
    sol = lltOfA.solve(b) ;
    cout << "Solution = " << sol << '\n' ;
    
    // solve the problem using least squares
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> Mat(N,2) ;
    Mat.col(0) = x ;
    Mat.col(1).fill(1) ; // fill column by ones!
    
    sol = Mat.colPivHouseholderQr().solve(y) ;
    
    cout << "Solution (LS) = " << sol << '\n' ;

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

