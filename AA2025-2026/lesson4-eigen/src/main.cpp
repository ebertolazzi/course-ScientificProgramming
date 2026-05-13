#include "eigen_fmt_lesson.h"

void demo_basics();
void demo_matrix_operations();
void demo_linear_systems();
void demo_eigenvalues();
void demo_geometry();
void demo_sparse();
void demo_advanced();
void demo_benchmarks();

int main() {
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "\n");
    fmt::print("╔══════════════════════════════════════════════════════════════════╗\n");
    fmt::print("║        EIGEN + {{fmt}} COMPLETE LESSON                       ║\n");
    fmt::print("║        Linear Algebra with Modern C++17                        ║\n");
    fmt::print("╚══════════════════════════════════════════════════════════════════╝\n\n");
    
    fmt::print(fg(fmt::color::green), "  Eigen: C++ template library for linear algebra\n");
    fmt::print(fg(fmt::color::green), "  {{fmt}}: Modern formatting library (v12)\n\n");
    
    print_title("MODULE 1: EIGEN BASICS");
    demo_basics();
    
    print_title("MODULE 2: MATRIX OPERATIONS");
    demo_matrix_operations();
    
    print_title("MODULE 3: LINEAR SYSTEMS");
    demo_linear_systems();
    
    print_title("MODULE 4: EIGENVALUES & DECOMPOSITIONS");
    demo_eigenvalues();
    
    print_title("MODULE 5: GEOMETRY");
    demo_geometry();
    
    print_title("MODULE 6: SPARSE MATRICES");
    demo_sparse();
    
    print_title("MODULE 7: ADVANCED TECHNIQUES");
    demo_advanced();
    
    print_title("MODULE 8: BENCHMARKS");
    demo_benchmarks();
    
    print_title("LESSON SUMMARY");
    fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "\n  Topics Covered:\n\n");
    fmt::print("  1. Vectors, matrices, initialization, block operations\n");
    fmt::print("  2. Matrix arithmetic, broadcasting, reductions\n");
    fmt::print("  3. Linear systems: LU, QR, Cholesky, SVD\n");
    fmt::print("  4. Eigenvalues: symmetric, general, PCA, power iteration\n");
    fmt::print("  5. Geometry: quaternions, rotations, 3D transforms\n");
    fmt::print("  6. Sparse matrices: construction, CG solver, Laplacian\n");
    fmt::print("  7. Advanced: expressions, Map, aliasing, STL\n");
    fmt::print("  8. Benchmarks: Eigen vs naive, memory patterns\n");
    
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "\n╔══════════════════════════════════════════════════════════════════╗\n");
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "║                  END OF EIGEN LESSON                           ║\n");
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "╚══════════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}
