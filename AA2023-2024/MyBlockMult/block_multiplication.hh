// Perform block multiplication of two matrices

#pragma once

#ifndef BLOCK_MUTIPLICATION_HH
#define BLOCK_MUTIPLICATION_HH

// Disable Eigen parallelism
#define EIGEN_DONT_PARALLELIZE

#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <thread>

#include "ThreadPool1.hh"


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

/*
Function to perform the block multiplication of a two matricies
*/
void
block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C
);

/*
Time and run the multiplication of two matrices multiple times and return the
average time and standard deviation
*/
std::pair<double, double>
time_standard_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     num_runs
);

std::pair<double, double>
time_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     num_runs
);

#endif