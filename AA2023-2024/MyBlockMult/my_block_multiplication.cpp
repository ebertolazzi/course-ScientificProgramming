// Perform block multiplication of two matrices

// Disable Eigen parallelism

#include "my_block_multiplication.hh"


/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Division of columns of A (AND C !!)
"D" is divided in "N" parts, with dimension "a"
  - standard dimension:   n_n
  - last block dimension: D-(N-1)*n_n
The iterator over the block is i_n {0, N-1} ( i_a = i_n*n_n )
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Division of rows of A (and columns of B)
"E" is divided in "P" parts, with dimension "b"
  - standard dimension:   n_p
  - last block dimension: E-(P-1)*n_p
The iterator over the block is i_p {0, P-1} ( i_b = i_p*n_p )
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Division of rows of B (AND C !!)
"G" is divided in "M" parts, with dimension "c"
  - standard dimension:   n_m
  - last block dimension: G-(M-1)*n_m
The iterator over the block is i_m {0, M-1} ( i_c = i_m*n_m )
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

Utils::ThreadPool1 TP1(12);

void
single_block_mult(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C,
  int                     E,
  int                     P,
  int                   n_p,
  int                   i_a,
  int                   i_c,
  int                     a,
  int                     c
) {

  // Extract the subblock of C
  auto CC = C.block(i_a , i_c , a , c); 

  // Loop over i_a-th block-row of A and i_c-th block-column of B
  for ( int i_p = 0 ; i_p < P ; ++i_p ){

    /* 
    i_b is the starting index of the i_p-th block with dimension 
      - axb (in the matrix A)
      - bxc (in the matrix B)
    */

    int b;
    int i_b = i_p*n_p;
    if (i_p == P-1){
      b =  E-i_b;
    } else {
      b = n_p;
    }

    // Multiplication of block matricies
    CC.noalias() = CC + A.block(i_a, i_b, a, b) * B.block(i_b, i_c, b, c);
  }

}

void
My_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C,
  int             const   N,
  int             const   P,
  int             const   M
) {

  // Dimension of matrix A
  int D{ int(A.rows()) };
  int E{ int(A.cols()) };

  // Dimension of matrix B (rows of B == cols of A for definition)
  // int E{ int(B.rows()) };
  int G{ int(B.cols()) };

  C = Eigen::MatrixXd::Zero(D,G);

  // "Ideal" dimensions of the blocks (do not consider the rest)
  int n_n{ D / N };
  int n_p{ E / P };
  int n_m{ G / M };

  int a, c; 
  int i_a, i_c;

  /* 
  Loop over the block of the matrix C 
    - N block-rows
    - M block-columns
  When iterator reaches the end of the block-row/col the block may be smaller (due to the rest of the division in block)
  */
  for (int i_n = 0; i_n < N; ++i_n){

    // i_a is the index of the block-row of C ; 
    // a   is the actual dimension of the block-row of C
    i_a = i_n*n_n;
    if (i_n == N-1){
      a = D-i_a;
    } else{
      a = n_n;
    }

    for (int i_m = 0; i_m < M; ++i_m){

      // i_c is index of the block-column of C ; 
      // c   is the actual dimension of the block-column of C 
      i_c = i_m*n_m;
      if (i_m == M-1){
        c = G-i_c;
      } else{
        c = n_m;
      }

      // update the block of C ( C.block(i_a , i_c , a , c); )
      TP1.run( 
        [&A, &B, &C, E, P, n_p, i_a, i_c, a, c](){ 
          single_block_mult(A, B, C, E, P, n_p, i_a, i_c, a, c); 
        }
      );

    }
    TP1.wait();

  }
}


std::pair<double, double>
My_time_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     N,
  int                     P,
  int                     M,
  int                     num_runs
) {

  // Create a matrix to store the result of the multiplication
  Eigen::MatrixXd C;

  Eigen::ArrayXd times;
  times.resize( num_runs );

  // Time the multiplication of the two matrices
  for (int i = 0; i < num_runs; i++) {

    auto start = std::chrono::high_resolution_clock::now();

    // Perform the multiplication
    My_block_multiplication( A, B, C, N, P, M );

    auto end = std::chrono::high_resolution_clock::now();

    // Compute the time taken in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;
    times(i) = duration.count();

    // check is the norm of the matrix residual (A*B - C)
    double check = (A*B - C).norm();
    if (check > 1E-8) {
      std::cout << "Norm od the residual matrix: (A*B - C) = " << check << std::endl << std::endl;
      std::cout << "Matrix product (using my block multiplication) is wrong!\nPlease check the code\n\n";
      exit(0);
    }
    

  }

  // Compute the average time and standard deviation
  double average_time       = times.mean();
  double standard_deviation = sqrt( (times-average_time).square().sum() / (num_runs-1) );
  return std::make_pair(average_time, standard_deviation);
}