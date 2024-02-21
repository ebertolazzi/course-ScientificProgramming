// ██████╗ ███████╗ ██████╗ ██╗   ██╗███████╗███████╗████████╗
// ██╔══██╗██╔════╝██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝
// ██████╔╝█████╗  ██║   ██║██║   ██║█████╗  ███████╗   ██║
// ██╔══██╗██╔══╝  ██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║
// ██║  ██║███████╗╚██████╔╝╚██████╔╝███████╗███████║   ██║
// ╚═╝  ╚═╝╚══════╝ ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝
//
// Write a C++11 or later program that utilizes the Eigen3 library to perform matrix-matrix multiplication using block partitioning.
// Given matrices A and B, compute the matrix C = A * B. Matrices A and B must be compatible for multiplication. Given the integers N, P, M, partition the matrices as follows:
//  - Matrix A into N x P blocks
//  - Matrix B into P x M blocks
//  - Matrix C into N x M blocks
// Ensure that the partitioning is compatible. If matrices A and B are incompatible, or if the required partitioning (N, P, M) is not possible, throw an exception.
// Each (i, j) block of matrix C must be computed on a separate thread if available, enabling parallel code execution.
// Finally, compare the execution speed of your block partitioning matrix multiplication with the timing of the standard Eigen3 matrix multiplication command.
// Use the proposed ThreadPool to find a better one to perform parallel tasks.

#include <iostream>
#include <timer.hh>
#include <BlockMult.hh>

// eigen do not parallelize
#define EIGEN_DONT_PARALLELIZE

#include <Eigen/Core>

int main()
{
  // ████████╗███████╗███████╗████████╗
  // ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝
  //    ██║   █████╗  ███████╗   ██║
  //    ██║   ██╔══╝  ╚════██║   ██║
  //    ██║   ███████╗███████║   ██║
  //    ╚═╝   ╚══════╝╚══════╝   ╚═╝

  Eigen::initParallel();
  std::cout << "Eigen Test" << std::endl;
  double mean   = 0.0;
  double stdDev = 0.0;
  Eigen::MatrixXd M1, M2, M3a, M3b;
  int n_runs = 100;
  Eigen::VectorXd times(n_runs);
  Eigen::VectorXd stdDev_vec(n_runs);
  int n_size = 300;
  int p_size = 200;
  int m_size = 500;
  int N = 10;
  int P = 10;
  int M = 10;
  M1.resize(n_size,p_size);
  M2.resize(p_size,m_size);
  M3a.resize(n_size,m_size);
  M3b.resize(n_size,m_size);

  M1 = Eigen::MatrixXd::Random(n_size,p_size);
  M2 = Eigen::MatrixXd::Random(p_size,m_size);

  // ███████╗████████╗ █████╗ ███╗   ██╗██████╗  █████╗ ██████╗ ██████╗
  // ██╔════╝╚══██╔══╝██╔══██╗████╗  ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗
  // ███████╗   ██║   ███████║██╔██╗ ██║██║  ██║███████║██████╔╝██║  ██║
  // ╚════██║   ██║   ██╔══██║██║╚██╗██║██║  ██║██╔══██║██╔══██╗██║  ██║
  // ███████║   ██║   ██║  ██║██║ ╚████║██████╔╝██║  ██║██║  ██║██████╔╝
  // ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝

  std::cout << "Standard Product\n";
  for (int i = 0; i < n_runs; i++) {
    mytimer t;
    M3a = M1 * M2;
    times(i) = t.elapsed();
  }
  mean   = times.mean();
  stdDev = (((times.array() - mean) * (times.array() - mean)).sqrt()).sum()/((double)(n_runs-1));
  std::cout  << "time: " << mean << " ms : " << stdDev << " ms (sdev)\n";

  std::cout << "Block Product\n";
  BlockMult::BlockMult BM;
  // test

  BM.set_NO();
  for (int i = 0; i < n_runs; i++) {
    mytimer t;
    BM.multiply( M1, M2, M3b, N, P, M );
    times(i) = t.elapsed();
  }
  mean   = times.mean();
  stdDev = (((times.array() - mean) * (times.array() - mean)).sqrt()).sum()/((double)(n_runs-1));
  std::cout  << "time (NO): " << mean << " ms : " << stdDev << " ms (sdev)\n";

  BM.set_TN();
  for (int i = 0; i < n_runs; i++) {
    mytimer t;
    BM.multiply( M1, M2, M3b, N, P, M );
    times(i) = t.elapsed();
  }
  mean   = times.mean();
  stdDev = (((times.array() - mean) * (times.array() - mean)).sqrt()).sum()/((double)(n_runs-1));
  std::cout  << "time (TN): " << mean << " ms : " << stdDev << " ms (sdev)\n";

  BM.set_BS();
  for (int i = 0; i < n_runs; i++) {
    mytimer t;
    BM.multiply( M1, M2, M3b, N, P, M );
    times(i) = t.elapsed();
  }
  mean   = times.mean();
  stdDev = (((times.array() - mean) * (times.array() - mean)).sqrt()).sum()/((double)(n_runs-1));
  std::cout  << "time (BS): " << mean << " ms : " << stdDev << " ms (sdev)\n";

  std::cout
    << "Check if the results are the same\n"
    << "M3a - M3b: " << (M3a- M3b).norm()
    << '\n';

  return 0;
}
