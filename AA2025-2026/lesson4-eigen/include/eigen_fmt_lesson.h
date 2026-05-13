#ifndef EIGEN_FMT_LESSON_H
#define EIGEN_FMT_LESSON_H

// {fmt}
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#include <fmt/chrono.h>

// Eigen
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <Eigen/SVD>
#include <Eigen/QR>
#include <Eigen/Cholesky>
#include <Eigen/LU>

// Standard
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <chrono>
#include <random>
#include <cmath>
#include <cstdint>

// ---------------------------------------------------------------------------
// Type aliases
// ---------------------------------------------------------------------------
using Vector2d = Eigen::Vector2d;
using Vector3d = Eigen::Vector3d;
using Vector4d = Eigen::Vector4d;
using VectorXd = Eigen::VectorXd;

using Matrix2d = Eigen::Matrix2d;
using Matrix3d = Eigen::Matrix3d;
using Matrix4d = Eigen::Matrix4d;
using MatrixXd = Eigen::MatrixXd;

using SparseMatrix = Eigen::SparseMatrix<double>;
using Triplet = Eigen::Triplet<double>;

// ---------------------------------------------------------------------------
// Helper: format a matrix into a string (works around fmt 12 limitations)
// ---------------------------------------------------------------------------
template <typename Derived>
std::string matrix_to_string(const Eigen::MatrixBase<Derived>& mat, int precision = 4) {
    std::string result;
    if (mat.rows() > 1 || mat.cols() > 1) {
        result += std::to_string(mat.rows()) + "x" + std::to_string(mat.cols()) + " matrix:\n";
    }
    for (int i = 0; i < mat.rows(); ++i) {
        result += "  ";
        for (int j = 0; j < mat.cols(); ++j) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%*.*f ", 10, precision, mat(i, j));
            result += buf;
        }
        if (i < mat.rows() - 1) result += "\n";
    }
    return result;
}

template <typename Derived>
std::string matrix_to_string_compact(const Eigen::MatrixBase<Derived>& mat, int precision = 4) {
    std::string result;
    if (mat.rows() == 1) {
        result = "[";
        for (int j = 0; j < mat.cols(); ++j) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.*f", precision, mat(0, j));
            result += buf;
            if (j < mat.cols() - 1) result += ", ";
        }
        result += "]";
    } else {
        result = "[";
        for (int i = 0; i < mat.rows(); ++i) {
            for (int j = 0; j < mat.cols(); ++j) {
                char buf[32];
                snprintf(buf, sizeof(buf), "%.*f", precision, mat(i, j));
                result += buf;
                if (j < mat.cols() - 1) result += ", ";
            }
            if (i < mat.rows() - 1) result += "; ";
        }
        result += "]";
    }
    return result;
}

// ---------------------------------------------------------------------------
// Utility functions
// ---------------------------------------------------------------------------
inline void print_title(const std::string& title) {
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "\n┌{:─>66}┐\n", "");
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "│  {:^62} │\n", title);
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "└{:─>66}┘\n", "");
}

inline void print_subtitle(const std::string& subtitle) {
    fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold,
               "\n┌{:─>50}┐\n", "");
    fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold,
               "│ {:<48} │\n", subtitle);
    fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold,
               "└{:─>50}┘\n", "");
}

// Random matrix
inline MatrixXd random_matrix(int rows, int cols, double min_val = -1.0, double max_val = 1.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min_val, max_val);
    MatrixXd mat(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat(i, j) = dis(gen);
    return mat;
}

// SPD matrix
inline MatrixXd spd_matrix(int n) {
    MatrixXd A = random_matrix(n, n, -1, 1);
    return A * A.transpose() + MatrixXd::Identity(n, n) * n;
}

// ===========================================================================
// MACRO to print matrices (works around fmt 12 formatter issues)
// Usage: PRINT_MAT(A) or PRINT_MAT_CPT(A, 2)
// ===========================================================================
#define PRINT_MAT(m) fmt::print("{}", matrix_to_string((m)))
#define PRINT_MAT_CPT(m, p) fmt::print("{}", matrix_to_string_compact((m), (p)))

#endif
