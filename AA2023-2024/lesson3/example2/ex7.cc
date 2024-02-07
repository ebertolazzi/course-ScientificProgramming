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
#include <tuple>

// try catch standard error classes
#include <exception>

using namespace std;

std::mutex mtx;

//
// f(x,y,z) = x^2-x*log(y)*exp(z-x)
//
// the class is not thread safe
class gradient {

  mutable std::mutex mtx;

  mutable std::map<std::thread::id,tuple<double,double,double>> args_id;
  mutable std::map<std::thread::id,tuple<double,double,double>> grad_id;

  void
  eval_grad( double x, double y, double z ) const {

    std::thread::id th_id = std::this_thread::get_id();
    tuple<double,double,double> * args;
    tuple<double,double,double> * grad;
    {
      std::lock_guard<std::mutex> lock(mtx);
      args = &args_id[th_id];
      grad = &grad_id[th_id];
    }

    //cout << "\nenter eval_grad\n";
    // check if already computed
    if ( ! (std::get<0>(*args) == x &&
            std::get<1>(*args) == y &&
            std::get<2>(*args) == z) ) {
      //cout << "\ncompute gradient\n";
      // store the arguments
      std::get<0>(*args) = x;
      std::get<1>(*args) = y;
      std::get<2>(*args) = z;
      double t2 = log(y);
      double t4 = exp(z-x);
      double t7 = x*t2*t4;
      //std::this_thread::sleep_for(std::chrono::milliseconds(10));
      // store the gradient
      std::get<0>(*grad) = -t2*t4+t7+2.0*x;
      std::get<1>(*grad) = -x/y*t4;
      std::get<2>(*grad) = -t7;
    }
  }

public:

  double operator () ( double x, double y, double z ) const {
    return x*x-x*log(y)*exp(z-x);
  }

  double Dx( double x, double y, double z ) const {
    tuple<double,double,double> * grad;
    std::thread::id th_id = std::this_thread::get_id();
    {
      std::lock_guard<std::mutex> lock(mtx);
      grad = &grad_id[th_id];
    }
    this->eval_grad( x, y, z );
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return std::get<0>(*grad);
  }
  double Dy( double x, double y, double z ) const {
    tuple<double,double,double> * grad;
    std::thread::id th_id = std::this_thread::get_id();
    {
      std::lock_guard<std::mutex> lock(mtx);
      grad = &grad_id[th_id];
    }
    this->eval_grad( x, y, z );
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return std::get<1>(*grad);
  }
  double Dz( double x, double y, double z ) const {
    tuple<double,double,double> * grad;
    std::thread::id th_id = std::this_thread::get_id();
    {
      std::lock_guard<std::mutex> lock(mtx);
      grad = &grad_id[th_id];
    }
    this->eval_grad( x, y, z );
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return std::get<2>(*grad);
  }

};

static gradient F;

static
void
eval( double x, double y, double z, int idx ) {
  char escape{0x1B};

  double Fe = F(x,y,z);
  double Fx = F.Dx(x,y,z);
  double Fy = F.Dy(x,y,z);
  double Fz = F.Dz(x,y,z);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  if ( idx == 1 ) { // critical section
    std::lock_guard<std::mutex> lock(mtx);
    std::cout
      << escape << '[' << 31+idx << 'm' // escape sequence for color
      << "idx = " << idx << '\n'
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

  std::vector<std::unique_ptr<std::thread>> th_eval1_vec;

  // create and launch of the threads using unique_ptr for automatic
  // deallocation
  eval ( x1, y1, z1, 1 );

  for ( int i = 0; i < 1000; ++i ) {
    th_eval1_vec.emplace_back( new std::thread( eval, x0, y0, z0, 0 ) );
  }

  eval( x1, y1, z1, 1 );

  for ( auto const & t : th_eval1_vec ) t->join();

  cout << "Thats all Folks!!\n";
  return 0;
}
