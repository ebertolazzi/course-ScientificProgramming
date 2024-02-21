#include <BlockMult.hh>

#define TH_POOL 1

namespace BlockMult {

  //-----------------------------------------------------

  BlockMult::BlockMult()
  : BS_pool{12}
  , TN_pool{12}
  {
  }

  //-----------------------------------------------------

  BlockMult::~BlockMult() {}

  //-----------------------------------------------------

  bool
  BlockMult::multiply(
    mat const & A,
    mat const & B,
    mat       & C,
    integer     n,
    integer     m,
    integer     p
  ) {

    if ( A.cols() != B.rows())  {
      std::cerr << "Invalid matrix multiplication. Found " << A.cols() << "x" << A.rows() << " Times " << B.cols() << "x" << B.rows() << std::endl;
      return false;
    }
    // get dimensions
    integer N{A.rows()};
    integer M{B.cols()};
    integer P{A.cols()};

    if ( n > N )  {
      std::cerr << "Invalid matrix multiplication. Found n = " << n << " > N " << N << std::endl;
      return false;
    }
    if ( m > M )  {
      std::cerr << "Invalid matrix multiplication. Found m = " << m << " > M " << M << std::endl;
      return false;
    }
    if ( p > P )  {
      std::cerr << "Invalid matrix multiplication. Found p = " << p << " > P " << P << std::endl;
      return false;
    }

    i_block.clear(); i_block.reserve(n+1); i_block.emplace_back(0);
    k_block.clear(); k_block.reserve(p+1); k_block.emplace_back(0);
    j_block.clear(); j_block.reserve(m+1); j_block.emplace_back(0);

    {
      int dn{int(N/n)};
      while ( i_block.back() < N )
        i_block.emplace_back( i_block.back() + dn );
      i_block.back() = N;
    }

    {
      int dm{int(M/m)};
      while ( j_block.back() < M )
        j_block.emplace_back( j_block.back() + dm );
      j_block.back() = M;
    }

    {
      int dp{int(P/p)};
      while ( k_block.back() < P )
        k_block.emplace_back( k_block.back() + dp );
      k_block.back() = P;
    }

    //
    #ifndef UNITN
    std::vector<std::future<void>> futures;
    #endif
    //
    switch ( m_choose ) {
      case choose_algo::NO_THREAD:
        for(integer i = 1; i < i_block.size(); ++i ) {
          for(integer j = 1; j < j_block.size(); ++j ) {
            Compute_C_block( A, B, C, i, j );
          }
        }
      break;
      case choose_algo::BS_THREAD:
        for(integer i = 1; i < i_block.size(); ++i ) {
          for(integer j = 1; j < j_block.size(); ++j ) {
            futures.push_back(
              BS_pool.submit_task(
                [this, &A, &B, &C, i, j](){this->Compute_C_block( A, B, C, i, j );}
              )
            );
          }
        }
        for(auto &f : futures) f.get();
      break;
      case choose_algo::TN_THREAD:
        for(integer i = 1; i < i_block.size(); ++i ) {
          for(integer j = 1; j < j_block.size(); ++j ) {
            TN_pool.run(
              [this, &A, &B, &C, i, j](){ this->Compute_C_block( A, B, C, i, j ); }
            );
            //TN_pool.run( &BlockMult::Compute_C_block, this, A, B, C, i, j );
          }
        }
        TN_pool.wait();
      break;
    }
    return true;
  }

  //-----------------------------------------------------

  void
  BlockMult::Compute_C_block(
    mat const & A,
    mat const & B,
    mat       & C,
    integer     i,
    integer     j
  ) {
    auto II = Eigen::seqN( i_block[i-1], i_block[i]-i_block[i-1] );
    auto JJ = Eigen::seqN( j_block[j-1], j_block[j]-j_block[j-1] );
    C(II,JJ).setZero();
    for ( integer k{1}; k < k_block.size(); ++k ) {
      auto KK = Eigen::seqN( k_block[k-1], k_block[k]-k_block[k-1] );
      C(II,JJ) += A(II,KK)*B(KK,JJ);
    }
  }

}

//-----------------------------------------------------
