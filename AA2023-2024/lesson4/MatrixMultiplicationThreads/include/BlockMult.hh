#ifndef BLOCKMULT_HH
#define BLOCKMULT_HH

#include <iostream>

#include <string>
#include <chrono>
#include <thread>

#include <timer.hh>

#include <Eigen/Core>

#include <BS_thread_pool.hpp>
#include <ThreadPool1.hh>

namespace BlockMult {

  using mat     = Eigen::MatrixXd;
  using integer = Eigen::Index;

  class BlockMult {

    enum class choose_algo {
      NO_THREAD = 1,
      BS_THREAD = 2,
      TN_THREAD = 3
    };

    choose_algo m_choose{choose_algo::NO_THREAD};

    std::mutex mtx;
    BS::thread_pool    BS_pool;
    Utils::ThreadPool1 TN_pool;

    std::vector<integer> i_block;
    std::vector<integer> j_block;
    std::vector<integer> k_block;

    // (n x m) * (m x p)
    void
    Compute_C_block(
      mat const & A,
      mat const & B,
      mat       & C,
      integer     i,
      integer     j
    );

  public:
    BlockMult();

    bool
    multiply(
      mat const & A,
      mat const & B,
      mat       & C,
      integer     n,
      integer     m,
      integer     p
    );

    ~BlockMult();

    void set_TN() { m_choose = choose_algo::TN_THREAD; }
    void set_BS() { m_choose = choose_algo::BS_THREAD; }
    void set_NO() { m_choose = choose_algo::NO_THREAD; }

  };

}

#endif