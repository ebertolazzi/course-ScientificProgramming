#include "eigen_fmt_lesson.h"

void demo_sparse() {
    print_subtitle("Sparse Matrices and Solvers");
    
    const int N = 100;
    std::vector<Triplet> triplets;
    triplets.reserve(3*N);
    for (int i = 0; i < N; ++i) {
        triplets.emplace_back(i, i, 2.0);
        if (i > 0)   triplets.emplace_back(i, i-1, -1.0);
        if (i < N-1) triplets.emplace_back(i, i+1, -1.0);
    }
    
    SparseMatrix A(N, N);
    A.setFromTriplets(triplets.begin(), triplets.end());
    A.makeCompressed();
    
    fmt::print(fg(fmt::color::green), "\n  Tridiagonal Sparse Matrix\n");
    fmt::print("    {}x{} sparse, {} non-zeros, density={:.2f}%\n",
               N, N, A.nonZeros(), 100.0 * A.nonZeros() / (N*N));
    
    // Dense 5x5 view
    MatrixXd As(5, 5);
    for (int i = 0; i < 5; ++i) {
        As(i,i) = 2.0;
        if (i > 0) As(i,i-1) = -1.0;
        if (i < 4) As(i,i+1) = -1.0;
    }
    fmt::print("    First 5x5:\n"); PRINT_MAT(As); fmt::print("\n");
    
    // Sparse LU
    fmt::print(fg(fmt::color::green), "\n  SparseLU Solver\n");
    VectorXd b = VectorXd::Ones(N);
    Eigen::SparseLU<SparseMatrix> lu;
    lu.compute(A);
    if (lu.info() == Eigen::Success) {
        VectorXd x = lu.solve(b);
        fmt::print("    ||Ax-b|| = {:.2e}\n", (A*x - b).norm());
        fmt::print("    First 5 values: {}\n", fmt::join(x.head(5), ", "));
    }
    
    // Conjugate Gradient
    fmt::print(fg(fmt::color::green), "\n  Conjugate Gradient (SPD)\n");
    SparseMatrix Aspd(N, N);
    std::vector<Triplet> ts;
    ts.reserve(3*N);
    for (int i = 0; i < N; ++i) {
        ts.emplace_back(i, i, 4.0);
        if (i > 0)   ts.emplace_back(i, i-1, -1.0);
        if (i < N-1) ts.emplace_back(i, i+1, -1.0);
    }
    Aspd.setFromTriplets(ts.begin(), ts.end());
    
    Eigen::ConjugateGradient<SparseMatrix, Eigen::Lower|Eigen::Upper> cg;
    cg.setTolerance(1e-6);
    cg.compute(Aspd);
    VectorXd x_cg = cg.solve(b);
    
    fmt::print("    Iterations: {}\n", cg.iterations());
    fmt::print("    Error: {:.2e}\n", cg.error());
    fmt::print("    ||Ax-b|| = {:.2e}\n", (Aspd*x_cg - b).norm());
    
    // 2D Laplacian
    fmt::print(fg(fmt::color::green), "\n  2D Laplacian\n");
    const int nx = 10, ny = 10, nt = nx*ny;
    SparseMatrix L(nt, nt);
    std::vector<Triplet> lt;
    lt.reserve(5*nt);
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            int idx = i + j*nx;
            lt.emplace_back(idx, idx, -4.0);
            if (i > 0)    lt.emplace_back(idx, idx-1, 1.0);
            if (i < nx-1) lt.emplace_back(idx, idx+1, 1.0);
            if (j > 0)    lt.emplace_back(idx, idx-nx, 1.0);
            if (j < ny-1) lt.emplace_back(idx, idx+nx, 1.0);
        }
    }
    L.setFromTriplets(lt.begin(), lt.end());
    
    fmt::print("    {}x{} grid: {} non-zeros vs {} dense\n", nx, ny, L.nonZeros(), nt*nt);
    fmt::print("    Compression: {:.1f}x\n", static_cast<double>(nt*nt) / L.nonZeros());
}
