#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#include <iostream>
#include <string>
#include <random>

using Matrix3d = Eigen::Matrix3d;
using MatrixXd = Eigen::MatrixXd;
using Vector3d = Eigen::Vector3d;
using VectorXd = Eigen::VectorXd;

// Helper to format matrix
template <typename Derived>
std::string mat_str(const Eigen::MatrixBase<Derived>& m, int prec = 4) {
    std::string s;
    for (int i = 0; i < m.rows(); ++i) {
        s += "  ";
        for (int j = 0; j < m.cols(); ++j) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%*.*f ", 10, prec, m(i,j));
            s += buf;
        }
        if (i < m.rows() - 1) s += "\n";
    }
    return s;
}

MatrixXd spd_matrix(int n) {
    MatrixXd A = MatrixXd::Random(n, n);
    return A * A.transpose() + MatrixXd::Identity(n, n) * n;
}

int main() {
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "\n  EIGEN + {{fmt}} QUICK DEMO (fmt 12.1.0)\n\n");
    
    Matrix3d A;
    A << 1, 2, 3, 4, 5, 6, 7, 8, 10;
    Vector3d b(1, 2, 3);
    
    fmt::print(fg(fmt::color::yellow), "  A:\n{}\n\n", mat_str(A));
    fmt::print(fg(fmt::color::yellow), "  b: {}\n\n", fmt::join(b, ", "));
    
    Vector3d x = A.lu().solve(b);
    fmt::print(fg(fmt::color::green), "  x = A⁻¹b: {}\n", fmt::join(x, ", "));
    fmt::print(fg(fmt::color::green), "  ||Ax-b|| = {:.2e}\n\n", (A*x - b).norm());
    
    fmt::print(fg(fmt::color::yellow), "  det(A) = {:.4f}\n", A.determinant());
    fmt::print(fg(fmt::color::yellow), "  A⁻¹:\n{}\n\n", mat_str(A.inverse()));
    
    Eigen::EigenSolver<Matrix3d> solver(A);
    fmt::print(fg(fmt::color::yellow), "  Eigenvalues:\n");
    for (int i = 0; i < solver.eigenvalues().size(); ++i) {
        auto lam = solver.eigenvalues()(i);
        fmt::print("    λ{} = {:8.4f} {:+8.4f}i\n", i, lam.real(), lam.imag());
    }
    
    Eigen::JacobiSVD<Matrix3d> svd(A);
    fmt::print(fg(fmt::color::yellow), "\n  Singular values: {}\n",
               fmt::join(svd.singularValues(), ", "));
    
    // Geometry
    Eigen::AngleAxisd rot(M_PI/4, Vector3d(0,0,1));
    Vector3d v(1, 0, 0);
    Vector3d vr = rot * v;
    fmt::print(fg(fmt::color::yellow), "\n  Rotate (1,0,0) by 45° Z: {}\n", fmt::join(vr, ", "));
    
    // SPD solve performance
    const int N = 200;
    MatrixXd big = spd_matrix(N);
    VectorXd bigb = VectorXd::Random(N);
    
    auto t1 = std::chrono::high_resolution_clock::now();
    VectorXd xlu = big.partialPivLu().solve(bigb);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto lu_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    
    t1 = std::chrono::high_resolution_clock::now();
    VectorXd xllt = big.llt().solve(bigb);
    t2 = std::chrono::high_resolution_clock::now();
    auto llt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    
    fmt::print(fg(fmt::color::yellow), "\n  {}x{} SPD solve:\n", N, N);
    fmt::print("    LU:  {} ms\n", lu_ms);
    fmt::print("    LLT: {} ms\n", llt_ms);
    
    fmt::print(fg(fmt::color::cyan), "\n  Eigen + {{fmt}} working!\n\n");
    return 0;
}
