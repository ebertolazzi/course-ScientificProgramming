#include "eigen_fmt_lesson.h"

void demo_matrix_operations() {
    print_subtitle("Arithmetic and Algebraic Operations");
    
    Matrix3d A, B;
    A << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    B << 9, 8, 7, 6, 5, 4, 3, 2, 1;
    
    // Basic arithmetic
    fmt::print(fg(fmt::color::green), "\n  Basic Arithmetic\n");
    fmt::print("    A:\n"); PRINT_MAT(A); fmt::print("\n");
    fmt::print("    B:\n"); PRINT_MAT(B); fmt::print("\n");
    fmt::print("    A + B:\n"); PRINT_MAT(A + B); fmt::print("\n");
    fmt::print("    A * 2.5:\n"); PRINT_MAT(A * 2.5); fmt::print("\n");
    fmt::print("    A * B (product):\n"); PRINT_MAT(A * B); fmt::print("\n");
    
    // Element-wise
    fmt::print(fg(fmt::color::green), "\n  Element-wise (.array())\n");
    fmt::print("    A.array() * B.array():\n"); PRINT_MAT(A*B); fmt::print("\n");
    fmt::print("    A.array().sqrt():\n"); PRINT_MAT(A.array().sqrt().matrix()); fmt::print("\n");
    
    // Inverse, determinant
    fmt::print(fg(fmt::color::green), "\n  Inverse & Determinant\n");
    MatrixXd C = random_matrix(3, 3, -2, 2);
    C = C * C.transpose() + MatrixXd::Identity(3, 3);
    
    fmt::print("    C (invertible):\n"); PRINT_MAT(C); fmt::print("\n");
    fmt::print("    C.inverse():\n"); PRINT_MAT(C.inverse()); fmt::print("\n");
    fmt::print("    C * C⁻¹:\n"); PRINT_MAT(C * C.inverse()); fmt::print("\n");
    fmt::print("    det(C) = {:.6f}\n", C.determinant());
    fmt::print("    trace(C) = {:.6f}\n", C.trace());
    
    // Vector operations
    fmt::print(fg(fmt::color::green), "\n  Vector Operations\n");
    Vector3d v1(1, 2, 3), v2(4, 5, 6);
    fmt::print("    v1 = {}\n", fmt::join(v1, ", "));
    fmt::print("    v2 = {}\n", fmt::join(v2, ", "));
    fmt::print("    dot(v1,v2) = {}\n", v1.dot(v2));
    fmt::print("    cross(v1,v2) = {}\n", fmt::join(v1.cross(v2), ", "));
    fmt::print("    angle = {:.2f}°\n", std::acos(v1.normalized().dot(v2.normalized())) * 180.0 / M_PI);
    fmt::print("    ||v1||₂ = {:.4f}\n", v1.norm());
    fmt::print("    v1.normalized() = {}\n", fmt::join(v1.normalized(), ", "));
    
    // Broadcasting
    fmt::print(fg(fmt::color::green), "\n  Broadcasting\n");
    MatrixXd M(3, 3);
    M << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    VectorXd v(3);
    v << 10, 20, 30;
    
    fmt::print("    M.colwise() + v:\n"); PRINT_MAT(M.colwise() + v); fmt::print("\n");
    
    // Reductions
    fmt::print(fg(fmt::color::green), "\n  Reductions\n");
    MatrixXd R = random_matrix(3, 4, 1, 10);
    fmt::print("    R (3x4):\n"); PRINT_MAT(R); fmt::print("\n");
    fmt::print("    R.sum() = {:.4f}\n", R.sum());
    fmt::print("    R.mean() = {:.4f}\n", R.mean());
    fmt::print("    R.minCoeff() = {:.4f}\n", R.minCoeff());
    fmt::print("    R.maxCoeff() = {:.4f}\n", R.maxCoeff());
    fmt::print("    R.norm() = {:.4f}\n", R.norm());
    fmt::print("    R.colwise().sum() = {}\n", fmt::join(R.colwise().sum(), ", "));
}
