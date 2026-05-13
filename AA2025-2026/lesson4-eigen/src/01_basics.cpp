#include "eigen_fmt_lesson.h"

void demo_basics() {
    print_subtitle("Vector and Matrix Initialization");
    
    // --- VECTORS ---
    fmt::print(fg(fmt::color::green), "\n  Vector Initialization\n");
    
    Vector2d v2(1.0, 2.0);
    Vector3d v3(1.0, 2.0, 3.0);
    
    VectorXd vd(5);
    vd << 1, 2, 3, 4, 5;
    
    VectorXd ones = VectorXd::Ones(4);
    VectorXd linspace = VectorXd::LinSpaced(5, 0.0, 10.0);
    VectorXd constant = VectorXd::Constant(4, 3.14);
    
    fmt::print("    Fixed v2:     {}\n", fmt::join(v2, ", "));
    fmt::print("    Fixed v3:     {}\n", fmt::join(v3, ", "));
    fmt::print("    Dynamic vd:   {}\n", fmt::join(vd, ", "));
    fmt::print("    Ones:         {}\n", fmt::join(ones, ", "));
    fmt::print("    LinSpaced:    {}\n", fmt::join(linspace, ", "));
    fmt::print("    Constant 3.14: {}\n", fmt::join(constant, ", "));
    
    fmt::print("\n    v3.norm() = {:.4f}\n", v3.norm());
    fmt::print("    v3.squaredNorm() = {:.4f}\n", v3.squaredNorm());
    fmt::print("    v3.sum() = {}\n", v3.sum());
    
    // --- MATRICES ---
    fmt::print(fg(fmt::color::green), "\n  Matrix Initialization\n");
    
    Matrix2d m2;
    m2 << 1, 2, 3, 4;
    
    Matrix3d m3;
    m3 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    
    MatrixXd md(3, 4);
    md << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;
    
    Matrix3d identity = Matrix3d::Identity();
    Matrix3d diag = Vector3d(1, 2, 3).asDiagonal();
    
    fmt::print("    Matrix2d:\n"); PRINT_MAT(m2); fmt::print("\n");
    fmt::print("    Identity 3x3:\n"); PRINT_MAT(identity); fmt::print("\n");
    fmt::print("    Diagonal(1,2,3):\n"); PRINT_MAT(diag); fmt::print("\n");
    fmt::print("    Dynamic 3x4:\n"); PRINT_MAT(md); fmt::print("\n");
    
    // --- BLOCK OPERATIONS ---
    fmt::print(fg(fmt::color::green), "\n  Block Operations\n");
    
    MatrixXd big = random_matrix(5, 5, 0, 10);
    MatrixXd top_left = big.block(0, 0, 2, 2);
    MatrixXd middle = big.block<2,3>(1, 1);
    VectorXd row2 = big.row(2);
    VectorXd col3 = big.col(3);
    
    fmt::print("    Big matrix 5x5:\n"); PRINT_MAT(big); fmt::print("\n");
    fmt::print("    Top-left 2x2:\n"); PRINT_MAT(top_left); fmt::print("\n");
    fmt::print("    Middle 2x3:\n"); PRINT_MAT(middle); fmt::print("\n");
    fmt::print("    Row 2: {}\n", fmt::join(row2, ", "));
    fmt::print("    Col 3: {}\n", fmt::join(col3, ", "));
    
    big.block(0, 0, 2, 2) = Matrix2d::Identity();
    fmt::print("    After top-left = I:\n"); PRINT_MAT(big); fmt::print("\n");
    
    // --- RESHAPE & MAP ---
    fmt::print(fg(fmt::color::green), "\n  Reshape and Map\n");
    
    MatrixXd orig(2, 6);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 6; ++j)
            orig(i, j) = i * 6 + j;
    
    fmt::print("    Original 2x6:\n"); PRINT_MAT(orig); fmt::print("\n");
    
    // Reshape returns a wrapper - need to assign to MatrixXd
    MatrixXd reshaped34 = orig.reshaped(3, 4);
    fmt::print("    Reshaped 3x4:\n"); PRINT_MAT(reshaped34); fmt::print("\n");
    
    // Map raw array
    double raw[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Eigen::Map<Matrix3d> mapped(raw);
    fmt::print("    Mapped from raw array:\n"); PRINT_MAT(mapped); fmt::print("\n");
}
