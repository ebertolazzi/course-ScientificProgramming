// Perform block multiplication of two matrices

// Disable Eigen parallelism

#include "block_multiplication.hh"

/*
  ______                                                    _        ___  
 |  ____|                                                  | |      |__ \ 
 | |__ _ __ ___  _ __ ___     _____  ____ _ _ __ ___  _ __ | | ___     ) |
 |  __| '__/ _ \| '_ ` _ \   / _ \ \/ / _` | '_ ` _ \| '_ \| |/ _ \   / / 
 | |  | | | (_) | | | | | | |  __/>  < (_| | | | | | | |_) | |  __/  / /_ 
 |_|  |_|  \___/|_| |_| |_|  \___/_/\_\__,_|_| |_| |_| .__/|_|\___| |____|
                                                     | |                  
                                                     |_|                  
*/

static Utils::ThreadPool1 TP(4);

/*
Function to perform the block multiplication of a two matricies
*/
void
block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C
) {
  
  Eigen::Index n{A.rows()};
  Eigen::Index m{B.cols()};
  Eigen::Index n_h{n/2};
  Eigen::Index m_h{m/2};

  auto const & A11 = A.topLeftCorner(n_h,m_h);
  auto const & A12 = A.topRightCorner(n_h,m-m_h);
  auto const & A21 = A.bottomLeftCorner(n-n_h,m_h);
  auto const & A22 = A.bottomRightCorner(n-n_h,m-m_h);

  auto const & B11 = B.topLeftCorner(n_h,m_h);
  auto const & B12 = B.topRightCorner(n_h,m_h);
  auto const & B21 = B.bottomLeftCorner(n_h,m_h);
  auto const & B22 = B.bottomRightCorner(n_h,m_h);

  auto C11 = C.topLeftCorner(n_h,m_h);
  auto C12 = C.topRightCorner(n_h,m_h);
  auto C21 = C.bottomLeftCorner(n_h,m_h);
  auto C22 = C.bottomRightCorner(n_h,m_h);

  #if 1
    #if 1
      TP.run( [&](){ C11.noalias() = A11*B11+A12*B21; } );
      TP.run( [&](){ C12.noalias() = A11*B12+A12*B22; } );
      TP.run( [&](){ C21.noalias() = A21*B11+A22*B21; } );
      TP.run( [&](){ C22.noalias() = A21*B12+A22*B22; } );
      TP.wait();
    #else
      std::thread th1( [&](){ C11.noalias() = A11*B11+A12*B21; } );
      std::thread th2( [&](){ C12.noalias() = A11*B12+A12*B22; } );
      std::thread th3( [&](){ C21.noalias() = A21*B11+A22*B21; } );
      std::thread th4( [&](){ C22.noalias() = A21*B12+A22*B22; } );
      th1.join();
      th2.join();
      th3.join();
      th4.join();
    #endif
  #else
  C11 = A11*B11+A12*B21;
  C12 = A11*B12+A12*B22;
  C21 = A21*B11+A22*B21;
  C22 = A21*B12+A22*B22;
  #endif
}



/*
Time and run the multiplication of two matrices multiple times and return the
average time and standard deviation
*/
std::pair<double, double>
time_standard_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     num_runs
) {
  // Create a matrix to store the result of the multiplication
  Eigen::MatrixXd C;//, C1;
  C.resize(A.cols(), B.rows());
  //C1.resize(A.cols(), B.rows());

  Eigen::ArrayXd times;
  times.resize( num_runs );

  // Time the multiplication of the two matrices
  for (int i = 0; i < num_runs; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    // Perform the multiplication
    C = A * B;
    //block_multiplication( A, B, C1 );
    //std::cout << (C-C1).norm() << '\n';
    //exit(0);

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


std::pair<double, double>
time_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     num_runs
) {
  // Create a matrix to store the result of the multiplication
  Eigen::MatrixXd C;
  C.resize(A.rows(), B.cols());

  Eigen::ArrayXd times;
  times.resize( num_runs );

  // Time the multiplication of the two matrices
  for (int i = 0; i < num_runs; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    // Perform the multiplication
    block_multiplication( A, B, C );
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