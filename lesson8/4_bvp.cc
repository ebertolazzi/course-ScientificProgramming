/*\
:|:  A simple program that compute approximate solution of
:|:  the boundary value problem
:|:
:|:  y(x)'' + p(x) y(x)' + q(x) y(x) = r(x)
:|:  y(a) = ya
:|:  y(b) = yb
:|:
:|:  by finite difference
\*/

#include <iostream>
#include <fstream>
#include <cmath>

// from STL
#include <string>
#include <vector>

#include <Eigen/Dense>

using namespace std ;

/*\
:|:  Parameter for the specific problem
:|:
:|:  y(x)'' + x * y(x)' - y(x) + x^2 = 0;
:|:
:|:  y(0) = 1, y(2) = 0
:|:
:|:  Exact solution
:|:
:|:         1    /1  2\   1  2   2
:|:  y(x) = - exp|- x | + - x  + -
:|:         3    \2   /   3      3
:|:
:|:                  /1  2\                 /1  (1/2)  \
:|:               exp|- x | (6 + exp(2)) erf|- 2      x|
:|:                  \2   /                 \2         /
:|:             - --------------------------------------
:|:                             / (1/2)\
:|:                        3 erf\2     / exp(2)
:|:
\*/

template <typename T>
class BVP {
public:

  typedef Eigen::Matrix<T,Eigen::Dynamic,1> vec;
  typedef T   real_type;
  typedef int int_type;

private:
  // tridiagonal system
  int_type  N;
  real_type h, a, b, ya, yb;
  vec       alpha, beta, gamma, omega, v, sol;

public:

  real_type X(int_type k) const { return a + k*h; }

  virtual real_type p( real_type x ) const = 0;
  virtual real_type q( real_type x ) const = 0;
  virtual real_type r( real_type x ) const = 0;
  virtual real_type exact( real_type x ) const { return 0; }

  /*
  Build the coefficient of the tridiagonal matrix
  for the problem
  
  // first row

      | alpha(0) gamma(0)       0        0        0  |
      |  beta(0) alpha(1) gamma(1)       0        0  |
  T = |        0  beta(1) alpha(2) gamma(2)       0  |
      |        0        0  beta(2) alpha(3) gamma(3) |
      |        0        0        0  beta(3) alpha(4) |
  

  b = [ omega[0], omega[1],...., omega[n-2] ]^T ;

   alpha(k)   = -2/h^2 + q(x[k+1])
   beta (k)   = 1/h^2 + p(x[k+2])/(2h)
   gamma(k)   = 1/h^2 - p(x[k+1])/(2h)
   omega(k)   = r(x[k+1])
   omega(0)   = r(x[1])-beta[0]*ya
   omega(N-2) = r(x[N-1])-gamma[N-2]*yb

 */

  void
  solve( int_type  N,  // number of interval of subdivision
         real_type a,  // left boundary
         real_type ya, // value of the solution on left boundary
         real_type b,  // right boundary
         real_type yb ) // value of the solution on right boundary
  {
    // some check
    if ( b <= a ) throw "bad interval" ; // interrupt the code with an exception
    if ( N <= 1 ) throw "N must be > 0" ;

    // compute the cell size
    this->a = a;
    this->b = b;
    this->N = N;
    this->h = (b-a)/(N+1);
  
    // initialize the vectors
    int_type n = N-1;
    alpha . resize(n);
    beta  . resize(n-1);
    gamma . resize(n-1);
    omega . resize(n);
    v     . resize(n);
    sol   . resize(n+2);

    // fill the vector alpha and omega
    for ( int_type k = 0 ; k < n ; ++k ) {
      real_type xkp1 = this->X(k+1);
      alpha(k) = -2/(h*h) + this->q(xkp1);
      omega(k) = this->r(xkp1);
    }
    for ( int_type k = 0 ; k < n-1; ++k ) {
      // fill the vector beta
      real_type xkp2 = this->X(k+2);
      beta(k) = 1/(h*h) + this->p(xkp2)/(2*h);
      // fill the vector gamma
      real_type xkp1 = this->X(k+1);
      gamma(k) = 1/(h*h) - p(xkp1)/(2*h);
    }

    omega(0)   = this->r(this->X(0))-beta(0)*ya;
    omega(n-1) = this->r(this->X(n))-gamma(n-2)*yb;

    // solve tridiagonal system
    real_type w = alpha(0);
    sol(0) = ya;
    sol(N) = yb;
    sol(1) = omega(0)/w;
    for ( int_type i=1; i < n; ++i ) {
      v(i-1) = gamma(i-1)/w;
      w      = alpha(i) - beta(i-1)*v(i-1);
      sol(i+1) = (omega(i) - beta(i-1)*sol(i) )/w;
    }
    for ( int_type j=n-2; j >= 0; --j )
      sol(j+1) -= v(j)*sol(j);
  }

  vec const & get_solution() const { return sol; }

  void
  save( string const & fname ) const {
    // open the file
    ofstream file( fname.c_str() ) ;

    // check if the file exist is opened etc.
    if ( file.bad() ) throw "error in openeing : result.txt\n" ;

    file << "x\ty\n" ;
    for ( int_type k = 0; k <= N; ++k )
      file << this->X(k) << "\t" << this->sol(k) << "\n" ;

    // close the file
    file.close() ;
  }

};

template <typename T>
class BVP_problem : public BVP<T> {
public:

  typedef typename BVP<T>::real_type real_type;
  typedef typename BVP<T>::int_type  int_type;
  typedef typename BVP<T>::vec       vec;

  virtual
  real_type
  p( real_type x ) const { return x; }

  virtual
  real_type
  q( real_type x ) const { return -1; }

  virtual
  real_type
  r( real_type x ) const { return x*x;}
};


template <typename T>
class BVP_problem2 : public BVP<T> {
public:

  typedef typename BVP<T>::real_type real_type;
  typedef typename BVP<T>::int_type  int_type;
  typedef typename BVP<T>::vec       vec;

  virtual
  real_type
  p( real_type x ) const { return x; }

  virtual
  real_type
  q( real_type x ) const { return -1; }

  virtual
  real_type
  r( real_type x ) const { return x*x;}
};

int
main( int argc, char * argv[] ) {

  //typedef BVP_problem<double> BVPP;
  typedef BVP_problem2<double> BVPP;

  BVPP::int_type N;

  if ( argc != 2 ) {
    cerr << "usage: " << argv[0] << " N\n";
    return 1;
  }

  // two argument, get number of interval from command line
  sscanf( argv[1], "%d", &N ) ;

  BVPP::real_type a  = 0;
  BVPP::real_type ya = 1;
  BVPP::real_type b  = 2;
  BVPP::real_type yb = 0;

  try {
    BVPP bvp;
    bvp.solve( N, a, ya, b, yb );
    // BVPP::vec const & sol = bvp.get_solution() ;
    bvp.save( "result.txt" );
  }
  catch ( char const msg[] ) {
    cerr << "Error found: " << msg << "\n" ;
    exit(0) ;
  }
  catch ( ... ) { // catch any kind of error
    cerr << "Unknown error\n" ;
    exit(0) ;
  }
}
