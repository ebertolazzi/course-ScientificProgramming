#include "dual.hh"

#include <TinyAD/Scalar.hh>
#include <TinyAD/ScalarFunction.hh>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @file test2.cc
 * @brief TinyAD validation and timing comparison against `AD::Dual`.
 */

namespace {

  //! Convenience alias for the custom dual number implementation.
  using DualNumber = AD::Dual<double>;

  //! First-order TinyAD scalar used for a fair comparison with `AD::Dual`.
  using TinyScalar = TinyAD::Scalar<1, double, false>;

  //! Second-order TinyAD scalar used to demonstrate Hessian support.
  using TinyScalar2 = TinyAD::Double<1>;

  //! Global sink used to prevent benchmark dead-code elimination.
  volatile double g_sink = 0.0;

  /**
   * @brief Stores the result of evaluating value and derivatives.
   */
  struct Evaluation {
    double value             = 0.0;
    double first_derivative  = 0.0;
    double second_derivative = 0.0;
  };

  /**
   * @brief Stores the result of a benchmark run.
   */
  struct TimingResult {
    double milliseconds = 0.0;
    double checksum     = 0.0;
  };

  /**
   * @brief Describes one timing scenario.
   */
  struct BenchmarkScenario {
    std::string name;
    int         sample_count         = 0;
    int         rounds_first_order   = 0;
    int         rounds_second_order  = 0;
  };

  /**
   * @brief Aggregated derivative-comparison statistics.
   */
  struct DerivativeComparisonStats {
    double max_abs_diff = 0.0;
    double max_rel_diff = 0.0;
  };

  /**
   * @brief Minimal context used to print and validate verbose tests.
   */
  struct TestContext {
    int total  = 0;
    int failed = 0;

    /**
     * @brief Prints a section title.
     *
     * @param title section name.
     */
    void section( std::string const & title ) const {
      std::cout << "\n== " << title << " ==\n";
    }

    /**
     * @brief Checks two scalar values and prints a verbose test line.
     *
     * @param label short description of the check.
     * @param actual computed value.
     * @param expected expected value.
     * @param tolerance absolute tolerance.
     */
    void expect_close(
      std::string const & label,
      double              actual,
      double              expected,
      double              tolerance = 1e-12
    ) {
      ++total;
      bool const ok = std::abs(actual - expected) <= tolerance;
      if ( !ok ) ++failed;

      std::ostream & out = ok ? std::cout : std::cerr;
      out
        << "Test " << total
        << ": " << label
        << " | expected " << expected
        << " | actual " << actual
        << " | tolerance " << tolerance
        << " | " << (ok ? "OK" : "FAIL")
        << '\n';
    }

    /**
     * @brief Finishes the run and throws if a check failed.
     */
    void finalize() const {
      std::cout << "\nSummary: executed " << total << " checks";
      if ( failed == 0 ) {
        std::cout << ", all passed.\n";
        return;
      }
      std::cout << ", failures: " << failed << ".\n";
      throw std::runtime_error("test2 failed");
    }
  };

  /**
   * @brief Smooth scalar function used for validation and timing.
   *
   * The domain is restricted to positive `x` values to keep all derivatives
   * finite for both AD implementations.
   *
   * @tparam T scalar type.
   * @param x function argument.
   * @return T function value.
   */
  template <typename T>
  T benchmark_function( T const & x ) {
    using std::atan;
    using std::cos;
    using std::exp;
    using std::log;
    using std::sin;
    using std::sqrt;

    T const numerator   = (x * x + T(2) * x + T(1)) * exp(sin(x));
    T const denominator = log(T(1) + x) + sqrt(x + T(2));
    T const tail        = cos(x) + atan(x / T(2));
    return numerator / denominator + tail;
  }

  /**
   * @brief Passive reference version of the benchmark function.
   *
   * @param x function argument.
   * @return double function value.
   */
  double benchmark_function_passive( double x ) {
    return benchmark_function(x);
  }

  /**
   * @brief Much larger expression used to stress the two AD implementations.
   *
   * The expression is intentionally long and repeatedly composes smooth
   * elementary functions to amplify instruction count and temporary creation.
   *
   * @tparam T scalar type.
   * @param x function argument.
   * @return T function value.
   */
  template <typename T>
  T huge_benchmark_function( T const & x ) {
    using std::atan;
    using std::cos;
    using std::exp;
    using std::log;
    using std::sin;
    using std::sqrt;

    T acc = T(0);

    for ( int i = 0; i < 40; ++i ) {
      T const c1 = T(0.02 + 0.005 * i);
      T const c2 = T(1.10 + 0.03 * i);
      T const c3 = T(2.50 + 0.04 * i);
      T const shifted_x = x + c1;
      T const local_a = benchmark_function(shifted_x / c2);
      T const local_b =
        exp(T(0.15) * sin(shifted_x)) /
        (sqrt(x + c2) + log(shifted_x * shifted_x + c3));
      T const local_c =
        (sin(local_a / c3) + cos(shifted_x / c2) + atan(shifted_x / c3));
      acc += (local_a + local_b + local_c + local_b * local_c) / (T(1.0) + c1);
    }

    return acc;
  }

  /**
   * @brief Passive reference version of the huge benchmark function.
   *
   * @param x function argument.
   * @return double function value.
   */
  double huge_benchmark_function_passive( double x ) {
    return huge_benchmark_function(x);
  }

  /**
   * @brief Evaluates the benchmark function with `AD::Dual`.
   *
   * @param x evaluation point.
   * @return Evaluation primal value and first derivative.
   */
  template <typename Function>
  Evaluation evaluate_dual_with( double x, Function const & function ) {
    DualNumber const active_x(x, 1.0);
    DualNumber const result = function(active_x);
    return {result.value(), result.dual(), 0.0};
  }

  /**
   * @brief Evaluates the benchmark function with `AD::Dual`.
   *
   * @param x evaluation point.
   * @return Evaluation primal value and first derivative.
   */
  Evaluation evaluate_dual( double x ) {
    return evaluate_dual_with(x, benchmark_function<DualNumber>);
  }

  /**
   * @brief Evaluates the huge benchmark function with `AD::Dual`.
   *
   * @param x evaluation point.
   * @return Evaluation primal value and first derivative.
   */
  Evaluation evaluate_dual_huge( double x ) {
    return evaluate_dual_with(x, huge_benchmark_function<DualNumber>);
  }

  /**
   * @brief Evaluates the benchmark function with first-order TinyAD.
   *
   * @param x evaluation point.
   * @return Evaluation primal value and first derivative.
   */
  template <typename Function>
  Evaluation evaluate_tinyad_first_order_with( double x, Function const & function ) {
    TinyScalar const active_x(x, 0);
    TinyScalar const result = function(active_x);
    return {result.val, result.grad(0), 0.0};
  }

  /**
   * @brief Evaluates the benchmark function with first-order TinyAD.
   *
   * @param x evaluation point.
   * @return Evaluation primal value and first derivative.
   */
  Evaluation evaluate_tinyad_first_order( double x ) {
    return evaluate_tinyad_first_order_with(x, benchmark_function<TinyScalar>);
  }

  /**
   * @brief Evaluates the huge benchmark function with first-order TinyAD.
   *
   * @param x evaluation point.
   * @return Evaluation primal value and first derivative.
   */
  Evaluation evaluate_tinyad_first_order_huge( double x ) {
    return evaluate_tinyad_first_order_with(x, huge_benchmark_function<TinyScalar>);
  }

  /**
   * @brief Evaluates the benchmark function with second-order TinyAD.
   *
   * @param x evaluation point.
   * @return Evaluation primal value, first derivative, and second derivative.
   */
  template <typename Function>
  Evaluation evaluate_tinyad_second_order_with( double x, Function const & function ) {
    TinyScalar2 const active_x(x, 0);
    TinyScalar2 const result = function(active_x);
    return {result.val, result.grad(0), result.Hess(0, 0)};
  }

  /**
   * @brief Evaluates the benchmark function with second-order TinyAD.
   *
   * @param x evaluation point.
   * @return Evaluation primal value, first derivative, and second derivative.
   */
  Evaluation evaluate_tinyad_second_order( double x ) {
    return evaluate_tinyad_second_order_with(x, benchmark_function<TinyScalar2>);
  }

  /**
   * @brief Evaluates the huge benchmark function with second-order TinyAD.
   *
   * @param x evaluation point.
   * @return Evaluation primal value, first derivative, and second derivative.
   */
  Evaluation evaluate_tinyad_second_order_huge( double x ) {
    return evaluate_tinyad_second_order_with(x, huge_benchmark_function<TinyScalar2>);
  }

  /**
   * @brief Approximates the second derivative with a centered finite difference.
   *
   * @param x evaluation point.
   * @param h finite-difference step.
   * @return double approximated second derivative.
   */
  double finite_difference_second_derivative( double x, double h = 1e-5 ) {
    return (
      benchmark_function_passive(x + h) -
      2.0 * benchmark_function_passive(x) +
      benchmark_function_passive(x - h)
    ) / (h * h);
  }

  /**
   * @brief Approximates the second derivative of the huge function.
   *
   * @param x evaluation point.
   * @param h finite-difference step.
   * @return double approximated second derivative.
   */
  double finite_difference_second_derivative_huge( double x, double h = 1e-5 ) {
    return (
      huge_benchmark_function_passive(x + h) -
      2.0 * huge_benchmark_function_passive(x) +
      huge_benchmark_function_passive(x - h)
    ) / (h * h);
  }

  /**
   * @brief Builds a set of sample points used by the benchmark.
   *
   * @param count number of samples.
   * @return std::vector<double> sample points in a safe domain.
   */
  std::vector<double> make_samples( int count ) {
    std::vector<double> samples;
    samples.reserve(static_cast<std::size_t>(count));

    for ( int i = 0; i < count; ++i ) {
      double const t = static_cast<double>(i) / static_cast<double>(count - 1);
      double const x = 0.15 + 1.35 * t + 0.015 * std::sin(19.0 * t);
      samples.push_back(x);
    }

    return samples;
  }

  /**
   * @brief Compares first derivatives computed by two evaluators over many points.
   *
   * @tparam DualEvaluator evaluator based on `dual.hh`.
   * @tparam TinyEvaluator evaluator based on TinyAD.
   * @param samples evaluation points.
   * @param dual_evaluator dual-number evaluator.
   * @param tiny_evaluator TinyAD evaluator.
   * @return DerivativeComparisonStats maximum absolute and relative differences.
   */
  template <typename DualEvaluator, typename TinyEvaluator>
  DerivativeComparisonStats compare_first_derivatives(
    std::vector<double> const & samples,
    DualEvaluator const      & dual_evaluator,
    TinyEvaluator const      & tiny_evaluator
  ) {
    DerivativeComparisonStats stats;

    for ( double x : samples ) {
      double const dual_derivative =
        dual_evaluator(x).first_derivative;
      double const tiny_derivative =
        tiny_evaluator(x).first_derivative;
      double const abs_diff = std::abs(dual_derivative - tiny_derivative);
      double const scale =
        std::max({1.0, std::abs(dual_derivative), std::abs(tiny_derivative)});
      double const rel_diff = abs_diff / scale;

      stats.max_abs_diff = std::max(stats.max_abs_diff, abs_diff);
      stats.max_rel_diff = std::max(stats.max_rel_diff, rel_diff);
    }

    return stats;
  }

  /**
   * @brief Benchmarks one evaluation routine over many samples and rounds.
   *
   * @tparam Evaluator callable returning `Evaluation`.
   * @param samples benchmark sample points.
   * @param rounds number of repeated passes.
   * @param evaluator function under test.
   * @return TimingResult elapsed time and checksum.
   */
  template <typename Evaluator>
  TimingResult run_benchmark(
    std::vector<double> const & samples,
    int                         rounds,
    Evaluator const           & evaluator
  ) {
    using Clock = std::chrono::steady_clock;

    auto const start = Clock::now();
    double checksum = 0.0;

    for ( int round = 0; round < rounds; ++round ) {
      for ( double x : samples ) {
        Evaluation const eval = evaluator(x);
        checksum += eval.value + 0.5 * eval.first_derivative + 0.05 * eval.second_derivative;
      }
    }

    auto const stop = Clock::now();
    g_sink += checksum;

    return {
      std::chrono::duration<double, std::milli>(stop - start).count(),
      checksum
    };
  }

  /**
   * @brief Validates TinyAD first-order mode against the custom dual numbers.
   *
   * @param ctx test context.
   */
  void test_tinyad_against_dual( TestContext & ctx ) {
    ctx.section("TinyAD first-order vs dual.hh");

    std::array<double, 6> const points{{0.15, 0.30, 0.50, 0.80, 1.10, 1.40}};
    for ( double x : points ) {
      Evaluation const dual_eval = evaluate_dual(x);
      Evaluation const tiny_eval = evaluate_tinyad_first_order(x);

      ctx.expect_close("value match at x=" + std::to_string(x), tiny_eval.value, dual_eval.value, 1e-12);
      ctx.expect_close("derivative match at x=" + std::to_string(x), tiny_eval.first_derivative, dual_eval.first_derivative, 1e-11);
    }

    DerivativeComparisonStats const stats = compare_first_derivatives(
      make_samples(250),
      evaluate_dual,
      evaluate_tinyad_first_order
    );
    ctx.expect_close("baseline derivative sweep max abs diff", stats.max_abs_diff, 0.0, 1e-10);
    ctx.expect_close("baseline derivative sweep max rel diff", stats.max_rel_diff, 0.0, 1e-12);
  }

  /**
   * @brief Validates TinyAD second-order mode against finite differences.
   *
   * @param ctx test context.
   */
  void test_tinyad_second_order( TestContext & ctx ) {
    ctx.section("TinyAD second-order check");

    std::array<double, 4> const points{{0.20, 0.45, 0.90, 1.25}};
    for ( double x : points ) {
      Evaluation const eval = evaluate_tinyad_second_order(x);
      double const fd2 = finite_difference_second_derivative(x);

      ctx.expect_close("second derivative at x=" + std::to_string(x), eval.second_derivative, fd2, 2e-5);
    }
  }

  /**
   * @brief Validates the large first-order expression against `dual.hh`.
   *
   * @param ctx test context.
   */
  void test_huge_expression_against_dual( TestContext & ctx ) {
    ctx.section("Huge expression: TinyAD first-order vs dual.hh");

    std::array<double, 4> const points{{0.18, 0.42, 0.78, 1.16}};
    for ( double x : points ) {
      Evaluation const dual_eval = evaluate_dual_huge(x);
      Evaluation const tiny_eval = evaluate_tinyad_first_order_huge(x);
      double const value_tol =
        1e-11 * std::max(1.0, std::abs(dual_eval.value));
      double const deriv_tol =
        1e-10 * std::max(1.0, std::abs(dual_eval.first_derivative));

      ctx.expect_close("huge value match at x=" + std::to_string(x), tiny_eval.value, dual_eval.value, value_tol);
      ctx.expect_close("huge derivative match at x=" + std::to_string(x), tiny_eval.first_derivative, dual_eval.first_derivative, deriv_tol);
    }

    DerivativeComparisonStats const stats = compare_first_derivatives(
      make_samples(180),
      evaluate_dual_huge,
      evaluate_tinyad_first_order_huge
    );
    ctx.expect_close("huge derivative sweep max abs diff", stats.max_abs_diff, 0.0, 2e-8);
    ctx.expect_close("huge derivative sweep max rel diff", stats.max_rel_diff, 0.0, 2e-12);
  }

  /**
   * @brief Validates the large second-order expression against finite differences.
   *
   * @param ctx test context.
   */
  void test_huge_expression_second_order( TestContext & ctx ) {
    ctx.section("Huge expression: TinyAD second-order check");

    std::array<double, 3> const points{{0.22, 0.67, 1.08}};
    for ( double x : points ) {
      Evaluation const eval = evaluate_tinyad_second_order_huge(x);
      double const fd2 = finite_difference_second_derivative_huge(x, 2e-5);
      double const tol = 2e-4 * std::max(1.0, std::abs(fd2));

      ctx.expect_close("huge second derivative at x=" + std::to_string(x), eval.second_derivative, fd2, tol);
    }
  }

  /**
   * @brief Tests the TinyAD `ScalarFunction` interface on the same function.
   *
   * @param ctx test context.
   */
  void test_tinyad_scalar_function( TestContext & ctx ) {
    ctx.section("TinyAD scalar_function interface");

    auto func = TinyAD::scalar_function<1>(TinyAD::range(1));
    func.template add_elements<1>(TinyAD::range(1), [] (auto & element) -> TINYAD_SCALAR_TYPE(element) {
      auto const x = element.variable(0);
      return benchmark_function(x);
    });

    Eigen::Matrix<double, 1, 1> x;
    x[0] = 0.75;

    auto const [f, g, H] = func.eval_with_derivatives(x);
    Evaluation const ref = evaluate_tinyad_second_order(x[0]);

    ctx.expect_close("scalar_function value", f, ref.value, 1e-12);
    ctx.expect_close("scalar_function gradient", g[0], ref.first_derivative, 1e-11);
    ctx.expect_close("scalar_function Hessian", H.coeff(0, 0), ref.second_derivative, 1e-10);
  }

  /**
   * @brief Prints one benchmark row.
   *
   * @param label row label.
   * @param result measured timing data.
   * @param evaluations total number of evaluations.
   * @param baseline_ns_per_eval baseline cost for ratios.
   */
  void print_benchmark_row(
    std::string const & label,
    TimingResult const & result,
    double              evaluations,
    double              baseline_ns_per_eval
  ) {
    double const ns_per_eval = result.milliseconds * 1.0e6 / evaluations;
    std::cout
      << label
      << " | elapsed_ms " << result.milliseconds
      << " | ns_per_eval " << ns_per_eval
      << " | checksum " << result.checksum;

    if ( baseline_ns_per_eval > 0.0 ) {
      std::cout << " | ratio_vs_dual " << (ns_per_eval / baseline_ns_per_eval);
    }

    std::cout << '\n';
  }

  /**
   * @brief Runs and prints the timing comparison.
   */
  void benchmark_tinyad_vs_dual() {
    std::cout << "\n== Timing comparison ==\n";

    std::array<BenchmarkScenario, 3> const scenarios{{
      {"baseline expression",      6000, 160,  80},
      {"huge expression",          2500,  60,  30},
      {"huge expression stress",    800, 220, 110}
    }};

    for ( BenchmarkScenario const & scenario : scenarios ) {
      std::vector<double> const samples = make_samples(scenario.sample_count);

      bool const huge = scenario.name.find("huge") != std::string::npos;

      TimingResult const dual_time = run_benchmark(
        samples,
        scenario.rounds_first_order,
        huge ? evaluate_dual_huge : evaluate_dual
      );
      TimingResult const tiny_first_time = run_benchmark(
        samples,
        scenario.rounds_first_order,
        huge ? evaluate_tinyad_first_order_huge : evaluate_tinyad_first_order
      );
      TimingResult const tiny_second_time = run_benchmark(
        samples,
        scenario.rounds_second_order,
        huge ? evaluate_tinyad_second_order_huge : evaluate_tinyad_second_order
      );

      double const dual_evaluations =
        static_cast<double>(scenario.sample_count) * static_cast<double>(scenario.rounds_first_order);
      double const tiny_second_evaluations =
        static_cast<double>(scenario.sample_count) * static_cast<double>(scenario.rounds_second_order);
      double const dual_ns_per_eval = dual_time.milliseconds * 1.0e6 / dual_evaluations;
      DerivativeComparisonStats const derivative_stats = compare_first_derivatives(
        samples,
        huge ? evaluate_dual_huge : evaluate_dual,
        huge ? evaluate_tinyad_first_order_huge : evaluate_tinyad_first_order
      );

      std::cout
        << "\nScenario: " << scenario.name
        << " | samples " << scenario.sample_count
        << " | first-order rounds " << scenario.rounds_first_order
        << " | second-order rounds " << scenario.rounds_second_order
        << " | max_abs_derivative_diff " << derivative_stats.max_abs_diff
        << " | max_rel_derivative_diff " << derivative_stats.max_rel_diff
        << '\n';

      print_benchmark_row("dual.hh first-order", dual_time, dual_evaluations, 0.0);
      print_benchmark_row("TinyAD first-order", tiny_first_time, dual_evaluations, dual_ns_per_eval);
      print_benchmark_row("TinyAD second-order", tiny_second_time, tiny_second_evaluations, dual_ns_per_eval);
    }
  }

}

/**
 * @brief Entry point of the TinyAD comparison program.
 *
 * @return int exit code `0` on success.
 */
int main() {
  try {
    std::cout << std::setprecision(12);

    TestContext ctx;
    test_tinyad_against_dual(ctx);
    test_tinyad_second_order(ctx);
    test_huge_expression_against_dual(ctx);
    test_huge_expression_second_order(ctx);
    test_tinyad_scalar_function(ctx);
    ctx.finalize();

    benchmark_tinyad_vs_dual();
  } catch ( std::exception const & exc ) {
    std::cerr << exc.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
