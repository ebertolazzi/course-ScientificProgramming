#include "eigen_fmt_lesson.h"

void demo_eigenvalues() {
    print_subtitle("Eigenvalues and Eigenvectors");
    
    // Self-adjoint
    fmt::print(fg(fmt::color::green), "\n  Self-Adjoint Eigenvalues\n");
    MatrixXd A = spd_matrix(4);
    Eigen::SelfAdjointEigenSolver<MatrixXd> solver(A);
    
    fmt::print("    Symmetric A:\n"); PRINT_MAT(A); fmt::print("\n");
    fmt::print("    Eigenvalues: {}\n", fmt::join(solver.eigenvalues(), ", "));
    fmt::print("    Eigenvectors:\n"); PRINT_MAT(solver.eigenvectors()); fmt::print("\n");
    
    for (int i = 0; i < 4; ++i) {
        double lam = solver.eigenvalues()(i);
        VectorXd v = solver.eigenvectors().col(i);
        fmt::print("    λ{} = {:8.4f}, ||Av-λv|| = {:.2e}\n", i, lam, (A*v - lam*v).norm());
    }
    
    // General
    fmt::print(fg(fmt::color::green), "\n  General Eigenvalues\n");
    MatrixXd B = random_matrix(3, 3);
    Eigen::EigenSolver<MatrixXd> gen(B);
    
    fmt::print("    Non-symmetric B:\n"); PRINT_MAT(B); fmt::print("\n");
    for (int i = 0; i < gen.eigenvalues().size(); ++i) {
        auto lam = gen.eigenvalues()(i);
        fmt::print("    λ{} = {:8.4f} {:+8.4f}i\n", i, lam.real(), lam.imag());
    }
    
    // Power iteration
    fmt::print(fg(fmt::color::green), "\n  Power Iteration\n");
    const int n = 50;
    MatrixXd P = spd_matrix(n);
    VectorXd vp = VectorXd::Random(n);
    vp.normalize();
    
    double lam_old = 0;
    int iter;
    for (iter = 0; iter < 1000; ++iter) {
        VectorXd Av = P * vp;
        double lam_new = Av.norm();
        vp = Av / lam_new;
        if (std::abs(lam_new - lam_old) < 1e-12) break;
        lam_old = lam_new;
    }
    
    Eigen::SelfAdjointEigenSolver<MatrixXd> exact(P);
    fmt::print("    Converged in {} iter\n", iter);
    fmt::print("    λ_max (power): {:.8f}\n", lam_old);
    fmt::print("    λ_max (exact): {:.8f}\n", exact.eigenvalues()(n-1));
    
    // PCA
    fmt::print(fg(fmt::color::green), "\n  PCA Demo\n");
    const int ns = 200;
    MatrixXd data(2, ns);
    std::random_device rd;
    std::mt19937 gen2(rd());
    std::normal_distribution<> noise(0, 0.15);
    
    for (int i = 0; i < ns; ++i) {
        double t = i * 0.05 - 5.0;
        data(0, i) = t + noise(gen2);
        data(1, i) = 0.75 * t + noise(gen2);
    }
    
    VectorXd mean = data.rowwise().mean();
    data.colwise() -= mean;
    MatrixXd cov = (data * data.transpose()) / (ns - 1);
    
    Eigen::SelfAdjointEigenSolver<MatrixXd> pca(cov);
    fmt::print("    Covariance:\n"); PRINT_MAT(cov); fmt::print("\n");
    fmt::print("    Eigenvalues: {}\n", fmt::join(pca.eigenvalues(), ", "));
    fmt::print("    Variance explained: {:.1f}%, {:.1f}%\n",
               100.0 * pca.eigenvalues()(0) / pca.eigenvalues().sum(),
               100.0 * pca.eigenvalues()(1) / pca.eigenvalues().sum());
}
