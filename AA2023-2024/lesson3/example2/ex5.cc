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
#include <mutex>

#include <map>

// try catch standard error classes
#include <exception>

using namespace std;

std::mutex mtx;

//
// f(x,y,z) = x^2-x*log(y)*exp(z-x)
//
// the class is not thread safe
class gradient {
  //double v{0};
  mutable double args[3]{0,0,0};
  mutable double g[3]{0,0,0};

  void
  eval_grad( double x, double y, double z ) const {
    cout << "\nenter eval_grad\n";
    // check if already computed
    if ( ! (args[0] == x && args[1] == y && args[2] == z) ) {
      cout << "\ncompute gradient\n";
      // store the arguments
      args[0] = x;
      args[1] = y;
      args[2] = z;
      double t2 = log(y);
      double t4 = exp(z-x);
      double t7 = x*t2*t4;
      // store the gradient
      g[0] = -t2*t4+t7+2.0*x;
      g[1] = -x/y*t4;
      g[2] = -t7;
    }
  }

public:

  double operator () ( double x, double y, double z ) const {
    return x*x-x*log(y)*exp(z-x);
  }

  double Dx( double x, double y, double z ) const {
    this->eval_grad( x, y, z );
    return g[0];
  }
  double Dy( double x, double y, double z ) const {
    this->eval_grad( x, y, z );
    return g[1];
  }
  double Dz( double x, double y, double z ) const {
    this->eval_grad( x, y, z );
    return g[2];
  }

};

static gradient F;

static
void
eval( double x, double y, double z, int idx ) {
  char escape{0x1B};

  double Fe = F(x,y,z);
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  double Fx = F.Dx(x,y,z);
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  double Fy = F.Dy(x,y,z);
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  double Fz = F.Dz(x,y,z);
  std::this_thread::sleep_for(std::chrono::milliseconds(250));

  { // critical section
    std::lock_guard<std::mutex> lock(mtx);
    std::cout
      << escape << '[' << 31+idx << 'm' // escape sequence for color
      << "F(x,y,z)    = " << Fe << '\n'
      << "DFDx(x,y,z) = " << Fx << '\n'
      << "DFDy(x,y,z) = " << Fy << '\n'
      << "DFDz(x,y,z) = " << Fz << '\n'
      << escape << '[' << 0 << 'm'; // reset to normal color/background
  }

}

int
main() {

  double x0{3.2}, y0{1.1}, z0{2.1};
  double x1{2.1}, y1{3.1}, z1{-1.1};

  //eval( x0, y0, z0, 0 );
  //eval( x1, y1, z1, 1 );

  std::thread th_eval1( eval, x0, y0, z0, 0 );
  std::thread th_eval2( eval, x1, y1, z1, 1 );

  th_eval1.join();
  th_eval2.join();

  cout << "Thats all Folks!!\n";
  return 0;
}
