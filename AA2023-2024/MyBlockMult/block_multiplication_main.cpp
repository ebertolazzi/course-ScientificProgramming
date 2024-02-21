

#include "block_multiplication.hh"
#include "my_block_multiplication.hh"


/* 

C = A*B

Dimension of the matricies:
  - A is a matrix D x E
  - B is a matrix E x G
  - C is a matrix D x G

Divide:
  - Matrix A in N x P blocks
  - Matrix B in P x M blocks
  - Matrix C in N x M blocks

*/

const int D = 81;
const int E = 76;
const int G = 12;

const int N = 10;
const int P = 10;
const int M = 10;

// Number of repetition to test the performance in terms of speed
int num_runs = 100;


int
main() {

  std::cout << "\033[1;0m" <<
  "C = A*B\n\n" <<
  "Dimension of the matricies:\n" <<
  "\t- A is a matrix D x E\n" <<
  "\t- B is a matrix E x G\n" <<
  "\t- C is a matrix D x G\n\n" <<
  "Divide:\n" <<
  "\t- Matrix A in N x P blocks\n" <<
  "\t- Matrix B in P x M blocks\n" <<
  "\t- Matrix C in N x M blocks\n\n";

  // Fix the random seed for reproducibility
  srand(0);

  // Define two random nxm matrices
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(D, E);
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(E, G);

  std::cout << std::endl;
  std::cout << "\033[1;32mStandard Eigen multiplication:" << std::endl;

  // Time the multiplication of the two matrices
  auto time_info = time_standard_multiplication(A, B, num_runs);

  std::cout << "\033[1;32mAverage time: " << time_info.first << " ms" << std::endl;
  std::cout << "\033[1;32mStandard deviation: " << time_info.second << " ms" << std::endl;
  
  std::cout << std::endl;
  std::cout << "\033[1;33mMatrix - block multiplication form example 2 (lesson 4):" << std::endl;
  if (D == E && E == G) {

    time_info = time_block_multiplication(A, B, num_runs);

    std::cout << "\033[1;33mAverage time: " << time_info.first << " ms" << std::endl;
    std::cout << "\033[1;33mStandard deviation: " << time_info.second << " ms" << std::endl;
  } else {
    std::cout << "\033[1;31mThis code works only for square matricies!" << std::endl;
  }
  
  std::cout << std::endl;
  std::cout << "\033[1;34mMatrix - my block multiplication (Matteo Tomasi):" << std::endl;
  
  time_info = My_time_block_multiplication(A, B, N, P, M, num_runs);

  std::cout << "\033[1;34mAverage time: " << time_info.first << " ms" << std::endl;
  std::cout << "\033[1;34mStandard deviation: " << time_info.second << " ms" << std::endl;

  std::cout << "\033[1;0m";

  return 0;
}
