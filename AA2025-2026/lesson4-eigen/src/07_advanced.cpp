#include "eigen_fmt_lesson.h"

void demo_advanced() {
    print_subtitle("Advanced Eigen Techniques");
    
    // Lazy evaluation
    fmt::print(fg(fmt::color::green), "\n  Lazy Evaluation\n");
    MatrixXd A = random_matrix(50, 50);
    MatrixXd B = random_matrix(50, 50);
    auto expr = A * B + A.transpose() * B;
    MatrixXd R = expr;
    fmt::print("    (A*B + Aᵀ*B) computed lazily: {}x{}\n", R.rows(), R.cols());
    
    // Nullary expression
    fmt::print(fg(fmt::color::green), "\n  Hilbert Matrix (NullaryExpr)\n");
    auto hilbert = [](int i, int j) { return 1.0 / (i + j + 1); };
    MatrixXd H = MatrixXd::NullaryExpr(5, 5, hilbert);
    fmt::print("    H(5x5):\n"); PRINT_MAT(H); fmt::print("\n");
    fmt::print("    det(H) = {:.6e}\n", H.determinant());
    
    // Map
    fmt::print(fg(fmt::color::green), "\n  Eigen::Map\n");
    std::vector<double> vec = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    Eigen::Map<Matrix3d> M(vec.data());
    fmt::print("    Mapped 3x3:\n"); PRINT_MAT(M); fmt::print("\n");
    
    M(0,0) = 999;
    fmt::print("    After M(0,0)=999: vec[0] = {}\n", vec[0]);
    
    // Aliasing
    fmt::print(fg(fmt::color::green), "\n  Aliasing & noalias()\n");
    MatrixXd X = random_matrix(3, 3);
    MatrixXd Y(3, 3);
    Y.noalias() = X * X;
    fmt::print("    X² (noalias):\n"); PRINT_MAT(Y); fmt::print("\n");
    
    // STL
    fmt::print(fg(fmt::color::green), "\n  STL Compatibility\n");
    VectorXd v = VectorXd::Random(8);
    std::vector<double> vc(v.data(), v.data() + v.size());
    std::sort(vc.begin(), vc.end());
    fmt::print("    Original: {}\n", fmt::join(v, ", "));
    fmt::print("    Sorted:   {}\n", fmt::join(vc, ", "));
}
