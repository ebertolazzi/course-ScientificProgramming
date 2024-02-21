#include <BlockMult.hh>

#define TH_POOL 1

//-----------------------------------------------------

BlockMult::BlockMult()
: pool{12}
{
}

//-----------------------------------------------------

BlockMult::BlockMult(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C,
  int                     n,
  int                     m,
  int                     p
) : pool{12}
{
  //
  multiply(A,B,C,n,m,p);
  //
  return;
}

//-----------------------------------------------------

BlockMult::~BlockMult()
{
}

//-----------------------------------------------------

void
BlockMult::multiply(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C,
  int                     n,
  int                     m,
  int                     p
)
{
  //
  if(!checkValidity(A,B,C))
  {
    std::cerr << "Invalid matrix multiplication!!!" << std::endl;
    return;
  }
  //
  #ifndef UNITN
  std::vector<std::future<void>> futures;
  #endif
  //
  for(int i = 0; i < C.rows() / n; i++) {
    for(int j = 0; j < C.cols() / m; j++) {
      #if TH_POOL
      #ifndef UNITN
      futures.push_back(
        pool.submit_task(
          [this, &A, &B, &C, n, m, p, i, j](){this->ComputeCBlock( A, B, C, n, m, p, i, j);})
        );
      #else
      pool.run(
        [this, &A, &B, &C, n, m, p, i, j](){this->ComputeCBlock( A, B, C, n, m, p, i, j);}
      );
      //pool.run( &BlockMult::ComputeCBlock, this, A, B, C, n, m, p, i, j );
      #endif
      #else
      ComputeCBlock( A, B, C, n, m, p, i, j);
      #endif
    }
  }
  //
  #ifndef UNITN
  for(auto &f : futures) f.get();
  #else
  pool.wait();
  #endif
  //
  return;
}

//-----------------------------------------------------

void
BlockMult::ComputeCBlock(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C,
  int                     n,
  int                     m,
  int                     p,
  int                     i,
  int                     j
) {
  auto && C_tmp = C.block( i * C.rows() / n, j * C.cols() / m, n, m);
  for(int k = 0; k < A.cols()/p; k++) {
    C_tmp +=  A.block( i * A.rows() / n, k * A.cols() / p, n, p ) *
              B.block( k * B.rows() / p, j * B.cols() / m, p, m );
  }
}

//-----------------------------------------------------

bool
BlockMult::checkValidity(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C
) {
  if(A.cols() != B.rows()) {
    std::cerr << "Invalid matrix multiplication. Found " << A.cols() << "x" << A.rows() << " Times " << B.cols() << "x" << B.rows() << std::endl;
    return false;
  }
  if(A.rows() != C.rows() || B.cols() != C.cols()) {
    std::cerr << "Invalid matrix multiplication. Found " << A.rows() << "x" << A.cols() << " Times " << B.rows() << "x" << B.cols() << " Expected to be " << C.rows() << "x" << C.cols() << std::endl;
    return false;
  }
  return true;
}

//-----------------------------------------------------
