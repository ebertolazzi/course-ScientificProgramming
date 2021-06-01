/*
 Some experiments using Eigen3

 -I/usr/local/include/eigen3  to add search of headers for eigen3 library

*/

// input output cin, cout, cerr
#include <iostream>

// better formatting, left, right, setw
#include <iomanip>

// is for STL vector container
#include <vector>

// sin, cos, exp
#include <cmath>

// for C++ string object
#include <string>     // C++ string

// for better error management
#include <exception>  // std::exception

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
generate_table(
  vector<T> & x,
  vector<T> & y,
  int         N
) {
  x.clear() ;
  y.clear() ;
  x.reserve(N) ;               
  y.reserve(N) ;
  
  for ( int i = 0 ; i < N ; ++i ) {
    T xx = ((rand() % 10000)-5000) * 0.001 ;
    T yy = func(xx) ;
    yy += ((rand() % 10000)-5000) * 0.0001 ;
    x.push_back(xx) ;
    y.push_back(yy) ;
  }

}

typedef float valueType ;

int
main() {

  try {
    int N = 100000000;
    vector<valueType> x, y ;
    generate_table( x, y, N ) ;
    
    // define a matrix od double (d) of size 2x2
    // Matrix2d = Matrix<double,2,2>
    Eigen::Matrix2d A;
    Eigen::Vector2d b, sol;
    
    // sum xi*xi
    valueType bf = 0 ;
    for ( int i = 0 ; i < N ; ++i ) bf += x[i]*x[i] ;
    A(0,0) = bf ;

    // sum xi
    bf = 0 ;
    for ( int i = 0; i < N ; ++i ) bf += x[i] ;
    A(1,0) = A(0,1) = bf ;
    A(1,1) = N ;

    // sum xi*yi
    bf = 0 ;
    for ( int i = 0; i < N ; ++i ) bf += x[i]*y[i] ;
    b(0) = bf ;

    // sum yi
    bf = 0 ;
    for ( int i = 0; i < N ; ++i ) bf += y[i] ;
    b(1) = bf ;
    
    // use Cholewsky decomposition
    Eigen::LLT<Eigen::Matrix2d> llt_Of_A(A);
    sol = llt_Of_A.solve(b) ;
    cout << "Solution (Cholewsky) = " << sol << '\n' ;
    
    // solve the problem using least squares
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> Mat(N,2) ;
    Eigen::Matrix<double,Eigen::Dynamic,1>              Rhs(N) ;
    for ( int i = 0 ; i < N ; ++i ) {
      Mat(i,0) = x[i] ;
      Mat(i,1) = 1 ;
      Rhs(i)   = y[i] ;
    }

    cout << "Mat^T * Mat =\n" << Mat.transpose() * Mat << '\n' ;
    cout << "A           =\n" << A << '\n' ;
    
    sol = Mat.colPivHouseholderQr().solve(Rhs) ;
    
    cout << "Solution (QR) = " << sol << '\n' ;

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

