#pragma once

#ifndef EXERCIZE3_HH
#define EXERCIZE3_HH

// {fmt}
#include <fmt/color.h>
#include <fmt/core.h>

// Eigen
#include <Eigen/Cholesky>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <Eigen/LU>
#include <Eigen/QR>
#include <Eigen/SVD>
#include <Eigen/Sparse>

// Standard
#include <chrono>
#include <cmath>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @mainpage Exercise 3 - A Lesson on Slices and Map in Eigen
 *
 * @tableofcontents
 *
 * @section overview Overview
 * This exercise has been turned into a compact guided lesson on how to
 * access submatrices and reinterpret existing memory through `Eigen::Map`.
 *
 * @section objectives Learning goals
 * - understand the difference between a copy and a view;
 * - use Eigen standard views such as `block`, `topLeftCorner`,
 *   `leftCols`, `rightCols`, and `middleCols`;
 * - use advanced slicing with `Eigen::indexing::seq`,
 *   `Eigen::indexing::all`, and `Eigen::indexing::last`;
 * - understand when `Eigen::Map` can read contiguous memory and when an
 *   `OuterStride` is required.
 *
 * @section key_idea Key idea
 * In Eigen a view does not own any data: it is only a window on memory that
 * already exists. This is true both for views created from an Eigen matrix
 * and for `Eigen::Map`, which binds an Eigen object to externally allocated
 * memory.
 *
 * @section layout Memory layout
 * `mat_type` uses Eigen's default layout, namely column-major storage.
 * This detail matters: consecutive coefficients in memory belong to the
 * same column, not to the same row.
 * For this reason:
 * - `A.topLeftCorner(2,2)` is the correct logical view of the upper-left
 *   block;
 * - `Eigen::Map<mat_type>(A.data(),2,2)` does not necessarily represent
 *   that block, because it only sees the first 4 contiguous values in
 *   memory;
 * - reconstructing a non-contiguous logical block requires the stride of
 *   the original matrix.
 *
 * @section build How to use the project
 * The program runs the lesson on screen, section by section.
 * The Doxygen comments document the rationale behind each operation and can
 * be used to generate HTML documentation when Doxygen is available.
 */

namespace Exercize3 {

  /// Floating point type used throughout the lesson.
  using real_type = double;

  /// Integer type used for indices and sizes.
  using integer = int;

  /// Dynamic dense matrix of real scalars.
  using mat_type = Eigen::Matrix<real_type,Eigen::Dynamic,Eigen::Dynamic>;

  /// Dynamic column vector of real scalars.
  using vec_type = Eigen::Matrix<real_type,Eigen::Dynamic,1>;

  /**
   * @brief Start a lightweight global timer.
   * @details The timer is intentionally simple and is used only to keep the
   * lesson self-contained.
   */
  void tic();

  /**
   * @brief Return the time elapsed since the last call to `tic`.
   * @return Elapsed time in milliseconds.
   */
  real_type toc();

  /**
   * @brief Build the reference matrix used by all examples.
   * @return A `3 x 10` matrix filled with easy-to-track values.
   *
   * @details
   * The values are arranged so that each column is immediately recognizable.
   * This makes it easier to understand when an operation is following the
   * logical matrix layout and when it is instead following the raw memory
   * layout.
   */
  mat_type make_reference_matrix();

  /**
   * @brief Print a colored section title.
   * @param title Title shown before a lesson block.
   */
  void print_section( std::string const & title );

  /**
   * @brief Print any dense Eigen expression without forcing a copy.
   * @tparam Derived Concrete Eigen type behind the expression.
   * @param title Label printed before the matrix.
   * @param M Dense matrix, block, slice or mapped view to print.
   *
   * @note `M` can be a matrix, a block, a corner view, a sliced expression,
   * or an `Eigen::Map`. The function accepts them all through Eigen's
   * expression template interface.
   */
  template <typename Derived>
  void
  print_matrix( std::string const & title, Eigen::DenseBase<Derived> const & M ) {
    std::cout << title << '\n';
    std::cout << M.derived() << "\n\n";
  }

  /**
   * @brief Introduce standard Eigen views such as `block` and `topLeftCorner`.
   *
   * @details
   * This lesson shows that these objects are views: changing the view changes
   * the original matrix. It is the preferred tool when the source object is
   * already an Eigen matrix.
   */
  void lesson_standard_views();

  /**
   * @brief Show what a basic `Eigen::Map` sees in column-major memory.
   *
   * @details
   * The example deliberately maps the first 4 contiguous coefficients of the
   * reference matrix. The output is useful to explain why a raw map does not
   * automatically coincide with the logical `topLeftCorner(2,2)`.
   */
  void lesson_basic_map();

  /**
   * @brief Reconstruct a logical block with `Eigen::Map` and `OuterStride`.
   *
   * @details
   * When the coefficients we want are not contiguous in memory, the map must
   * be told how far apart consecutive columns are. In a column-major matrix,
   * that distance is the outer stride.
   */
  void lesson_strided_map();

  /**
   * @brief Rebind `Eigen::Map` objects in place with placement new.
   *
   * @details
   * `Eigen::Map` does not behave like a reseatable pointer. Once built, it is
   * bound to a given address and shape. Reconstructing the object with
   * `new (&map) Eigen::Map<...>(...)` is a classic technique when the lesson
   * wants to reuse the same variable name for different mapped views.
   */
  void lesson_placement_new_map();

  /**
   * @brief Demonstrate column slices with `seq`, `all`, and `last`.
   *
   * @details
   * This lesson focuses on Eigen's indexing module, which is ideal when the
   * pattern is more expressive than a simple contiguous block.
   */
  void lesson_slices();

  /**
   * @brief Show an in-place assignment on slices.
   *
   * @details
   * Odd columns are overwritten with even columns. The example highlights that
   * slice expressions can appear on both sides of an assignment.
   */
  void lesson_slice_assignment();

}

#endif
