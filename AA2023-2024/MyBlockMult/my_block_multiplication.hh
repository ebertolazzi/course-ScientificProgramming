// Perform block multiplication of two matrices

#pragma once

#ifndef MY_BLOCK_MUTIPLICATION_HH
#define MY_BLOCK_MUTIPLICATION_HH

#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

#include "ThreadPool1.hh"


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
);

void
My_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  Eigen::MatrixXd       & C,
  int             const   N,
  int             const   P,
  int             const   M
);


std::pair<double, double>
My_time_block_multiplication(
  Eigen::MatrixXd const & A,
  Eigen::MatrixXd const & B,
  int                     N,
  int                     P,
  int                     M,
  int                     num_runs
);

#endif