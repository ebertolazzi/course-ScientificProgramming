#include "Newton.hh"

using real = double;

class Problem : public AD::NewtonProblemAD<real> {

public:

  Problem() {
    _x0.resize(2);
    _x0(0) = 2;
    _x0(1) = 1;
  }

  using AD::NewtonProblemAD<real>::F;
  using AD::NewtonProblemAD<real>::JF;

  d_dual_vec F( d_dual_vec const & X ) const override {
    d_dual_vec res;
    res.resize(2);
    auto const & x = X(0);
    auto const & y = X(1);
    res(0) = x+y-1.0;
    res(1) = x*x+y*y-2.0;
    return res;
  }
};

int main() {

  Problem problem;
  
  Problem::d_vec ip = problem.initial_point();
  
  Problem::d_vec F  = problem.F( ip );
  Problem::d_mat JF = problem.JF( ip );
  
  AD::NewtonSolver solver( &problem );
  
  //std::cout << "F = " << F << '\n';
  //std::cout << "JF\n" << JF << '\n';
  
  solver.solve(); // compute solution
  
  if ( solver.converged() ) {
    std::cout << "CONVERGED!!!!\n";
    std::cout << "x = " << solver.solution().transpose() << '\n' ;
  } else {
    std::cout << "FAILED!!!!\n";
  }

  return 0;
}
