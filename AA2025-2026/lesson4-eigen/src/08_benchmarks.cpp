#include "eigen_fmt_lesson.h"

class Timer {
    using Clock = std::chrono::high_resolution_clock;
    std::string name;
    Clock::time_point start;
public:
    Timer(std::string n) : name(std::move(n)), start(Clock::now()) {}
    double ms() const {
        return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
    }
    ~Timer() {
        fmt::print(fg(fmt::color::cyan), "    {}: {:.2f} ms\n", name, ms());
    }
};

void demo_benchmarks() {
    print_subtitle("Performance Benchmarks");
    
    // Matrix multiply
    fmt::print(fg(fmt::color::green), "\n  Matrix-Matrix Multiply\n");
    for (int N : {50, 100, 200}) {
        MatrixXd A = MatrixXd::Random(N, N);
        MatrixXd B = MatrixXd::Random(N, N);
        MatrixXd C(N, N);
        
        {
            Timer t(fmt::format("Eigen {}x{}", N, N));
            C.noalias() = A * B;
        }
        {
            Timer t(fmt::format("Naive {}x{}", N, N));
            C.setZero();
            for (int i = 0; i < N; ++i)
                for (int k = 0; k < N; ++k)
                    for (int j = 0; j < N; ++j)
                        C(i,j) += A(i,k) * B(k,j);
        }
        fmt::print("\n");
    }
    
    // Solvers
    fmt::print(fg(fmt::color::green), "\n  Linear Solvers (200x200 SPD)\n");
    MatrixXd A = spd_matrix(200);
    VectorXd b = VectorXd::Random(200);
    
    { Timer t("PartialPivLU"); VectorXd x = A.partialPivLu().solve(b); }
    { Timer t("LDLT        "); VectorXd x = A.ldlt().solve(b); }
    { Timer t("LLT         "); VectorXd x = A.llt().solve(b); }
    { Timer t("QR          "); VectorXd x = A.colPivHouseholderQr().solve(b); }
    
    // Memory access
    fmt::print(fg(fmt::color::green), "\n  Memory Access (column-major is faster)\n");
    const int M = 500;
    MatrixXd mat = MatrixXd::Random(M, M);
    
    {
        Timer t("Row-major (slow)");
        double s = 0;
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < M; ++j)
                s += mat(i,j);
        (void)s;
    }
    {
        Timer t("Col-major (fast)");
        double s = 0;
        for (int j = 0; j < M; ++j)
            for (int i = 0; i < M; ++i)
                s += mat(i,j);
        (void)s;
    }
    
    fmt::print(fg(fmt::color::yellow), "\n  Tip: Use -O3 -march=native -DNDEBUG for best performance\n");
}
