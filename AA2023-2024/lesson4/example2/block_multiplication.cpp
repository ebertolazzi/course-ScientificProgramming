// Perform block multiplication of two matrices

// Disable Eigen parallelism

#define EIGEN_DONT_PARALLELIZE

#include <Eigen/Dense>
#include <chrono>
#include <iostream>

// Time and run the multiplication of two matrices multiple times and return the
// average time and standard deviation
std::pair<double, double>
time_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     num_runs
) {
  // Create a matrix to store the result of the multiplication
  Eigen::MatrixXd C;
  C.resize(A.cols(), B.rows());

  Eigen::ArrayXd times;
  times.resize( num_runs );

  // Time the multiplication of the two matrices
  for (int i = 0; i < num_runs; i++) {

    auto start = std::chrono::high_resolution_clock::now();
    // Perform the multiplication
    C = A * B;
    auto end = std::chrono::high_resolution_clock::now();

    // Compute the time taken in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;
    times(i) = duration.count();
  }

  // Compute the average time and standard deviation
  double average_time       = times.mean();
  double standard_deviation = sqrt( (times-average_time).square().sum() / (num_runs-1) );
  return std::make_pair(average_time, standard_deviation);
}

int
main() {
  // Fix the random seed for reproducibility
  srand(0);

  // Define the matrices dimensions
  int n = 100;
  int m = 100;

  // Define two random nxm matrices
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, m);
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(m, n);

  // Time the multiplication of the two matrices
  int num_runs   = 1e3;
  auto time_info = time_block_multiplication(A, B, num_runs);

  std::cout << "Average time: " << time_info.first << " ms" << std::endl;
  std::cout << "Standard deviation: " << time_info.second << " ms" << std::endl;

  return 0;
}
