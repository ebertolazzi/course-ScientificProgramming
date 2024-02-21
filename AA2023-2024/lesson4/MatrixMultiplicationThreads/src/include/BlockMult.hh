#ifndef BLOCKMULT_HH
#define BLOCKMULT_HH

#include <iostream>

#include <string>
#include <chrono>
#include <thread>

#include <timer.hh>

#include <Eigen/Core>

#ifndef UNITN
#include <BS_thread_pool.hpp>
#else
#include <ThreadPool1.hh>
#endif

class BlockMult
{
private:
  #ifndef UNITN
  BS::thread_pool pool;
  // mutex
  std::mutex mtx;
  #else
  Utils::ThreadPool1 pool;
  #endif

public:
  BlockMult();
  BlockMult(
    Eigen::MatrixXd const & A,
    Eigen::MatrixXd const & B,
    Eigen::MatrixXd       & C,
    int                     n,
    int                     m,
    int                     p
  );

  void
  multiply(
    Eigen::MatrixXd const & A,
    Eigen::MatrixXd const & B,
    Eigen::MatrixXd       & C,
    int                     n,
    int                     m,
    int                     p
  );
  ~BlockMult();

private:

  bool
  checkValidity(
    Eigen::MatrixXd const & A,
    Eigen::MatrixXd const & B,
    Eigen::MatrixXd       & C
  );

  void
  ComputeCBlock(
    Eigen::MatrixXd const & A,
    Eigen::MatrixXd const & B,
    Eigen::MatrixXd       & C,
    int                     n,
    int                     m,
    int                     p,
    int                     i,
    int                     j
  );

};


#endif