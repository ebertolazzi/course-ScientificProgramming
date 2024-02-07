/*
example of ineheritance in C++11

*/

// standard header for I/O
#include <iostream>

// standard header C++ strings
#include <string>

// for timing
#include <chrono>

// for thread and in particular the function sleep_for
#include <thread>

#include <map>

// try catch standard error classes
#include <exception>

using namespace std;

//
// f(x,y,z) = x^2-x*log(y)*exp(z-x)
//
class gradient {
  //double v{0};
  mutable double g[3]{0,0,0};

  void
  eval_grad( double x, double y, double z ) const {
    double t2 = log(y);
    double t4 = exp(z-x);
    double t7 = x*t2*t4;
    g[0] = -t2*t4+t7+2.0*x;
    g[1] = -x/y*t4;
    g[2] = -t7;
  }

public:

  double operator () ( double x, double y, double z ) const {
    return x*x-x*log(y)*exp(z-x);
  }

  double Dx( double x, double y, double z ) const {
    eval_grad( x, y, z );
    return g[0];
  }
  double Dy( double x, double y, double z ) const {
    eval_grad( x, y, z );
    return g[1];
  }
  double Dz( double x, double y, double z ) const {
    eval_grad( x, y, z );
    return g[2];
  }

};

int
main() {

  gradient F;

  cout << "F(3.2,1.1,2.1) = " << F(3.2,1.1,2.1) << '\n';
  cout << "gradF(0,1,2) = [ "
       << F.Dx(3.2,1.1,2.1) << ' '
       << F.Dy(3.2,1.1,2.1) << ' '
       << F.Dz(3.2,1.1,2.1) << "]\n";

  cout << "Thats all Folks!!\n";
  return 0;
}
