#include "eigen_fmt_lesson.h"

void demo_linear_systems() {
    print_subtitle("Solving Linear Systems Ax = b");
    
    // LU
    fmt::print(fg(fmt::color::green), "\n  LU Decomposition\n");
    MatrixXd A = random_matrix(4, 4, -2, 2);
    A = A * A.transpose() + MatrixXd::Identity(4, 4);
    VectorXd b = VectorXd::Random(4);
    
    VectorXd x_lu = A.partialPivLu().solve(b);
    
    fmt::print("    A (4x4):\n"); PRINT_MAT(A); fmt::print("\n");
    fmt::print("    b: {}\n", fmt::join(b, ", "));
    fmt::print("    x (LU): {}\n", fmt::join(x_lu, ", "));
    fmt::print("    ||Ax - b|| = {:.2e}\n", (A * x_lu - b).norm());
    
    // QR
    fmt::print(fg(fmt::color::green), "\n  QR Decomposition\n");
    MatrixXd A_qr(5, 3);
    A_qr << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15;
    Eigen::ColPivHouseholderQR<MatrixXd> qr(A_qr);
    
    fmt::print("    A (5x3):\n"); PRINT_MAT(A_qr); fmt::print("\n");
    fmt::print("    Rank: {}\n", qr.rank());
    
    VectorXd b_qr = VectorXd::Random(5);
    VectorXd x_qr = qr.solve(b_qr);
    fmt::print("    Least squares residual = {:.6f}\n", (A_qr * x_qr - b_qr).norm());
    
    // Cholesky
    fmt::print(fg(fmt::color::green), "\n  Cholesky (SPD)\n");
    MatrixXd A_spd = spd_matrix(4);
    VectorXd b_chol = VectorXd::Random(4);
    
    Eigen::LDLT<MatrixXd> ldlt(A_spd);
    VectorXd x_ldlt = ldlt.solve(b_chol);
    
    Eigen::LLT<MatrixXd> llt(A_spd);
    VectorXd x_llt = llt.solve(b_chol);
    
    fmt::print("    SPD matrix:\n"); PRINT_MAT(A_spd); fmt::print("\n");
    fmt::print("    x (LDLT): {}\n", fmt::join(x_ldlt, ", "));
    fmt::print("    ||Ax-b|| = {:.2e}\n", (A_spd * x_ldlt - b_chol).norm());
    fmt::print("    x (LLT):  {}\n", fmt::join(x_llt, ", "));
    fmt::print("    ||Ax-b|| = {:.2e}\n", (A_spd * x_llt - b_chol).norm());
    
    // SVD
    fmt::print(fg(fmt::color::green), "\n  SVD Decomposition\n");
    MatrixXd A_svd = random_matrix(4, 3);
    Eigen::JacobiSVD<MatrixXd> svd(A_svd, Eigen::ComputeThinU | Eigen::ComputeThinV);
    
    fmt::print("    A (4x3):\n"); PRINT_MAT(A_svd); fmt::print("\n");
    fmt::print("    Singular values: {}\n", fmt::join(svd.singularValues(), ", "));
    
    // Solver comparison
    fmt::print(fg(fmt::color::green), "\n  Solver Speed (200x200 SPD)\n");
    const int N = 200;
    MatrixXd big_A = spd_matrix(N);
    VectorXd big_b = VectorXd::Random(N);
    
    auto t1 = std::chrono::high_resolution_clock::now();
    VectorXd x1 = big_A.partialPivLu().solve(big_b);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto lu_t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    
    t1 = std::chrono::high_resolution_clock::now();
    VectorXd x2 = big_A.ldlt().solve(big_b);
    t2 = std::chrono::high_resolution_clock::now();
    auto ldlt_t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    
    t1 = std::chrono::high_resolution_clock::now();
    VectorXd x3 = big_A.llt().solve(big_b);
    t2 = std::chrono::high_resolution_clock::now();
    auto llt_t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    
    fmt::print("    PartialPivLU: {} ms (err: {:.2e})\n", lu_t.count(), (big_A*x1-big_b).norm());
    fmt::print("    LDLT:         {} ms (err: {:.2e})\n", ldlt_t.count(), (big_A*x2-big_b).norm());
    fmt::print("    LLT:          {} ms (err: {:.2e})\n", llt_t.count(), (big_A*x3-big_b).norm());
}
