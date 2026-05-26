#include <TinyAD/ScalarFunction.hh>

#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/real.hpp>
#include <autodiff/forward/utils/derivative.hpp>

#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @file test4.cc
 * @brief Compares TinyAD and autodiff on a scalar objective with many variables.
 */

namespace {

  //! Number of scalar variables used in the benchmark objective.
  constexpr int kVariableCount = 12;

  //! Fixed-size vector storing the objective variables.
  using DenseVector = Eigen::Matrix<double, kVariableCount, 1>;

  //! Fixed-size dense Hessian used for comparisons and checksums.
  using DenseMatrix = Eigen::Matrix<double, kVariableCount, kVariableCount>;

  //! Sparse matrix type returned by TinyAD.
  using SparseMatrix = Eigen::SparseMatrix<double>;

  //! autodiff scalar type used for first-order gradient evaluations.
  using AutoReal = autodiff::real;

  //! autodiff scalar type used for second-order derivative evaluations.
  using AutoDual2 = autodiff::dual2nd;

  //! Fixed-size array of autodiff real numbers.
  using AutoRealArray = std::array<AutoReal, kVariableCount>;

  //! Fixed-size array of autodiff second-order dual numbers.
  using AutoDual2Array = std::array<AutoDual2, kVariableCount>;

  //! Global sink used to prevent dead-code elimination during timing.
  volatile double g_sink = 0.0;

  /**
   * @brief Stores a first-order evaluation.
   */
  struct GradientEvaluation {
    double      value = 0.0;
    DenseVector gradient = DenseVector::Zero();
  };

  /**
   * @brief Stores a second-order evaluation.
   */
  struct HessianEvaluation {
    double      value = 0.0;
    DenseVector gradient = DenseVector::Zero();
    DenseMatrix hessian = DenseMatrix::Zero();
  };

  /**
   * @brief Aggregates benchmark timing data.
   */
  struct TimingResult {
    double milliseconds = 0.0;
    double checksum     = 0.0;
  };

  /**
   * @brief Describes one timing scenario.
   */
  struct TimingScenario {
    std::string name;
    int         sample_count     = 0;
    int         gradient_rounds  = 0;
    int         hessian_rounds   = 0;
  };

  /**
   * @brief Tracks maximum discrepancies over a sweep of sample points.
   */
  struct SweepStatistics {
    double max_abs_gradient_diff = 0.0;
    double max_rel_gradient_diff = 0.0;
    double max_abs_hessian_diff  = 0.0;
    double max_rel_hessian_diff  = 0.0;
  };

  /**
   * @brief Prints verbose checks and aborts the run on failure.
   */
  struct TestContext {
    int total  = 0;
    int failed = 0;

    /**
     * @brief Prints a section header.
     *
     * @param title section title.
     */
    void section( std::string const & title ) const {
      std::cout << "\n== " << title << " ==\n";
    }

    /**
     * @brief Checks two scalar values with an absolute tolerance.
     *
     * @param label check description.
     * @param actual computed value.
     * @param expected expected value.
     * @param tolerance admissible absolute error.
     */
    void expect_close(
      std::string const & label,
      double              actual,
      double              expected,
      double              tolerance
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
     * @brief Finalizes the test session.
     */
    void finalize() const {
      std::cout << "\nSummary: executed " << total << " checks";
      if ( failed == 0 ) {
        std::cout << ", all passed.\n";
        return;
      }
      std::cout << ", failures: " << failed << ".\n";
      throw std::runtime_error("test4 failed");
    }
  };

  /**
   * @brief Builds a readable label for one vector component.
   *
   * @param prefix label prefix.
   * @param index component index.
   * @return std::string formatted label.
   */
  std::string component_label( std::string const & prefix, int index ) {
    std::ostringstream buffer;
    buffer << prefix << "[" << index << "]";
    return buffer.str();
  }

  /**
   * @brief Builds a readable label for one matrix entry.
   *
   * @param prefix label prefix.
   * @param row matrix row.
   * @param col matrix column.
   * @return std::string formatted label.
   */
  std::string matrix_label( std::string const & prefix, int row, int col ) {
    std::ostringstream buffer;
    buffer << prefix << "[" << row << "," << col << "]";
    return buffer.str();
  }

  /**
   * @brief Returns a smooth pairwise contribution to the objective.
   *
   * @tparam T scalar type.
   * @param index pair index.
   * @param xi left variable.
   * @param xj right variable.
   * @return T pair contribution.
   */
  template <typename T>
  T pair_term( int index, T const & xi, T const & xj ) {
    using std::exp;
    using std::log;
    using std::sin;

    T const mix      = xi * xj + T(0.07 * (index + 1));
    T const shifted  = T(1.0) + T(0.15) * xi * xi + T(0.11) * xj * xj;
    T const diff     = xi - T(0.8) * xj;
    T const diff2    = diff * diff;
    T const exp_arg  = T(0.03 * (index + 2)) * (xi + T(0.5) * xj);
    T const quartic  = T(0.01 * (index + 1)) * diff2 * diff2;
    return sin(mix) + exp(exp_arg) + log(shifted) + quartic;
  }

  /**
   * @brief Returns a dense global coupling term.
   *
   * @tparam T scalar type.
   * @param x full variable array.
   * @return T dense contribution.
   */
  template <typename T>
  T global_term( std::array<T, kVariableCount> const & x ) {
    using std::exp;
    using std::sin;

    T weighted_sum    = T(0);
    T oscillatory_sum = T(0);
    T dense_sum       = T(0);

    for ( int i = 0; i < kVariableCount; ++i ) {
      weighted_sum += T(0.2 + 0.03 * i) * x[i];
      oscillatory_sum += sin(T(0.4) * x[i] + T(0.1 * i));
    }

    for ( int i = 0; i < kVariableCount; ++i ) {
      for ( int j = i + 2; j < kVariableCount; ++j ) {
        dense_sum += T(0.0025) * x[i] * x[j] / T(1.0 + 0.1 * (i + j));
      }
    }

    return
      T(0.05) * weighted_sum * weighted_sum +
      exp(T(0.02) * oscillatory_sum) +
      dense_sum;
  }

  /**
   * @brief Full scalar objective used for correctness checks and timing.
   *
   * @tparam T scalar type.
   * @param x full variable array.
   * @return T objective value.
   */
  template <typename T>
  T scalar_objective( std::array<T, kVariableCount> const & x ) {
    T value = global_term(x);
    for ( int i = 0; i < kVariableCount - 1; ++i ) value += pair_term(i, x[i], x[i + 1]);
    return value;
  }

  /**
   * @brief Explicit 12-variable form used by autodiff derivative utilities.
   *
   * @tparam T scalar type.
   * @return T objective value.
   */
  template <typename T>
  T autodiff_objective_12(
    T const & x0,  T const & x1,  T const & x2,  T const & x3,
    T const & x4,  T const & x5,  T const & x6,  T const & x7,
    T const & x8,  T const & x9,  T const & x10, T const & x11
  ) {
    std::array<T, kVariableCount> x{{x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11}};
    return scalar_objective(x);
  }

  /**
   * @brief Converts a TinyAD sparse Hessian into a dense matrix.
   *
   * @param sparse source sparse matrix.
   * @return DenseMatrix dense matrix representation.
   */
  DenseMatrix to_dense( SparseMatrix const & sparse ) {
    DenseMatrix dense = DenseMatrix::Zero();
    for ( int col = 0; col < sparse.outerSize(); ++col ) {
      for ( SparseMatrix::InnerIterator it(sparse, col); it; ++it ) {
        dense(it.row(), it.col()) = it.value();
      }
    }
    return dense;
  }

  /**
   * @brief Converts a dense sample point into an autodiff real array.
   *
   * @param x sample point.
   * @return AutoRealArray converted array.
   */
  AutoRealArray to_autoreal_array( DenseVector const & x ) {
    AutoRealArray result{};
    for ( int i = 0; i < kVariableCount; ++i ) result[i] = x(i);
    return result;
  }

  /**
   * @brief Converts a dense sample point into an autodiff second-order array.
   *
   * @param x sample point.
   * @return AutoDual2Array converted array.
   */
  AutoDual2Array to_autodual2_array( DenseVector const & x ) {
    AutoDual2Array result{};
    for ( int i = 0; i < kVariableCount; ++i ) result[i] = x(i);
    return result;
  }

  /**
   * @brief Returns one autodiff variable by runtime index.
   *
   * @tparam ArrayType autodiff array type.
   * @param variables source array.
   * @param index requested position.
   * @return typename ArrayType::value_type& selected variable.
   */
  template <typename ArrayType>
  typename ArrayType::value_type &
  variable_at( ArrayType & variables, int index ) {
    switch ( index ) {
      case 0:  return variables[0];
      case 1:  return variables[1];
      case 2:  return variables[2];
      case 3:  return variables[3];
      case 4:  return variables[4];
      case 5:  return variables[5];
      case 6:  return variables[6];
      case 7:  return variables[7];
      case 8:  return variables[8];
      case 9:  return variables[9];
      case 10: return variables[10];
      default: return variables[11];
    }
  }

  /**
   * @brief Builds the TinyAD scalar objective.
   *
   * @return auto TinyAD scalar function object.
   */
  auto build_tinyad_objective() {
    TinyAD::EvalSettings settings;
    settings.n_threads = 1;

    auto function = TinyAD::scalar_function<1>(TinyAD::range(kVariableCount), settings);

    function.template add_elements<2>(TinyAD::range(kVariableCount - 1), [] (auto & element) -> TINYAD_SCALAR_TYPE(element) {
      using T = TINYAD_SCALAR_TYPE(element);
      int const i = element.handle;
      T const xi = element.variable(i);
      T const xj = element.variable(i + 1);
      return pair_term(i, xi, xj);
    });

    function.template add_elements<kVariableCount>(TinyAD::range(1), [] (auto & element) -> TINYAD_SCALAR_TYPE(element) {
      using T = TINYAD_SCALAR_TYPE(element);
      std::array<T, kVariableCount> x{};
      for ( int i = 0; i < kVariableCount; ++i ) x[i] = element.variable(i);
      return global_term(x);
    });

    return function;
  }

  /**
   * @brief Evaluates TinyAD in first-order mode.
   *
   * @tparam TinyFunction TinyAD scalar function type.
   * @param function TinyAD objective.
   * @param x evaluation point.
   * @return GradientEvaluation value and gradient.
   */
  template <typename TinyFunction>
  GradientEvaluation evaluate_tinyad_gradient(
    TinyFunction const & function,
    DenseVector const  & x
  ) {
    Eigen::VectorXd const x_dynamic = x;
    auto const [value, gradient] = function.eval_with_gradient(x_dynamic);
    GradientEvaluation result;
    result.value = value;
    result.gradient = gradient;
    return result;
  }

  /**
   * @brief Evaluates TinyAD in second-order mode.
   *
   * @tparam TinyFunction TinyAD scalar function type.
   * @param function TinyAD objective.
   * @param x evaluation point.
   * @return HessianEvaluation value, gradient, and Hessian.
   */
  template <typename TinyFunction>
  HessianEvaluation evaluate_tinyad_hessian(
    TinyFunction const & function,
    DenseVector const  & x
  ) {
    Eigen::VectorXd const x_dynamic = x;
    auto const [value, gradient, hessian] = function.eval_with_derivatives(x_dynamic);
    HessianEvaluation result;
    result.value = value;
    result.gradient = gradient;
    result.hessian = to_dense(hessian);
    return result;
  }

  /**
   * @brief Evaluates autodiff in first-order mode.
   *
   * @param x evaluation point.
   * @return GradientEvaluation value and gradient.
   */
  GradientEvaluation evaluate_autodiff_gradient( DenseVector const & x ) {
    using autodiff::at;
    using autodiff::derivative;
    using autodiff::wrt;

    AutoRealArray variables = to_autoreal_array(x);

    GradientEvaluation result;
    result.value = autodiff_objective_12(
      variables[0], variables[1], variables[2], variables[3],
      variables[4], variables[5], variables[6], variables[7],
      variables[8], variables[9], variables[10], variables[11]
    ).val();

    auto const at_all = [&] () {
      return at(
        variables[0], variables[1], variables[2], variables[3],
        variables[4], variables[5], variables[6], variables[7],
        variables[8], variables[9], variables[10], variables[11]
      );
    };

    for ( int i = 0; i < kVariableCount; ++i ) {
      result.gradient(i) = derivative(autodiff_objective_12<AutoReal>, wrt(variable_at(variables, i)), at_all());
    }

    return result;
  }

  /**
   * @brief Evaluates autodiff in second-order mode.
   *
   * @param x evaluation point.
   * @return HessianEvaluation value, gradient, and Hessian.
   */
  HessianEvaluation evaluate_autodiff_hessian( DenseVector const & x ) {
    using autodiff::at;
    using autodiff::derivative;
    using autodiff::val;
    using autodiff::wrt;

    AutoDual2Array variables = to_autodual2_array(x);

    auto const evaluate_value = [&] () -> AutoDual2 {
      return autodiff_objective_12(
        variables[0], variables[1], variables[2], variables[3],
        variables[4], variables[5], variables[6], variables[7],
        variables[8], variables[9], variables[10], variables[11]
      );
    };

    auto const at_all = [&] () {
      return at(
        variables[0], variables[1], variables[2], variables[3],
        variables[4], variables[5], variables[6], variables[7],
        variables[8], variables[9], variables[10], variables[11]
      );
    };

    HessianEvaluation result;
    result.value = val(evaluate_value());

    for ( int i = 0; i < kVariableCount; ++i ) {
      result.gradient(i) = derivative(autodiff_objective_12<AutoDual2>, wrt(variable_at(variables, i)), at_all());
    }

    for ( int i = 0; i < kVariableCount; ++i ) {
      for ( int j = i; j < kVariableCount; ++j ) {
        double const value = derivative<2>(
          autodiff_objective_12<AutoDual2>,
          wrt(variable_at(variables, i), variable_at(variables, j)),
          at_all()
        );
        result.hessian(i, j) = value;
        result.hessian(j, i) = value;
      }
    }

    return result;
  }

  /**
   * @brief Builds one deterministic sample point.
   *
   * @param sample_index sample identifier.
   * @param amplitude perturbation amplitude.
   * @return DenseVector sample vector.
   */
  DenseVector build_sample_point( int sample_index, double amplitude ) {
    DenseVector x;
    for ( int i = 0; i < kVariableCount; ++i ) {
      double const base = 0.35 + 0.045 * i;
      double const osc1 = std::sin(0.17 * sample_index + 0.31 * i);
      double const osc2 = std::cos(0.11 * sample_index * (i + 1) + 0.19 * i);
      x(i) = base + amplitude * (0.7 * osc1 + 0.3 * osc2);
    }
    return x;
  }

  /**
   * @brief Builds a set of deterministic benchmark samples.
   *
   * @param count number of samples.
   * @param amplitude perturbation amplitude.
   * @return std::vector<DenseVector> sample set.
   */
  std::vector<DenseVector> build_samples( int count, double amplitude ) {
    std::vector<DenseVector> samples;
    samples.reserve(static_cast<std::size_t>(count));
    for ( int i = 0; i < count; ++i ) samples.push_back(build_sample_point(i, amplitude));
    return samples;
  }

  /**
   * @brief Computes relative error with a symmetric scale.
   *
   * @param actual computed value.
   * @param expected reference value.
   * @return double relative difference.
   */
  double relative_difference( double actual, double expected ) {
    double const scale = std::max({1.0, std::abs(actual), std::abs(expected)});
    return std::abs(actual - expected) / scale;
  }

  /**
   * @brief Computes sweep statistics over multiple sample points.
   *
   * @tparam TinyFunction TinyAD function type.
   * @param tinyad_function TinyAD objective.
   * @param samples sample points.
   * @return SweepStatistics maximum discrepancies.
   */
  template <typename TinyFunction>
  SweepStatistics compute_sweep_statistics(
    TinyFunction const            & tinyad_function,
    std::vector<DenseVector> const& samples
  ) {
    SweepStatistics stats;

    for ( DenseVector const & x : samples ) {
      HessianEvaluation const tinyad   = evaluate_tinyad_hessian(tinyad_function, x);
      HessianEvaluation const autodiff = evaluate_autodiff_hessian(x);

      for ( int i = 0; i < kVariableCount; ++i ) {
        stats.max_abs_gradient_diff = std::max(
          stats.max_abs_gradient_diff,
          std::abs(tinyad.gradient(i) - autodiff.gradient(i))
        );
        stats.max_rel_gradient_diff = std::max(
          stats.max_rel_gradient_diff,
          relative_difference(tinyad.gradient(i), autodiff.gradient(i))
        );
      }

      for ( int i = 0; i < kVariableCount; ++i ) {
        for ( int j = 0; j < kVariableCount; ++j ) {
          stats.max_abs_hessian_diff = std::max(
            stats.max_abs_hessian_diff,
            std::abs(tinyad.hessian(i, j) - autodiff.hessian(i, j))
          );
          stats.max_rel_hessian_diff = std::max(
            stats.max_rel_hessian_diff,
            relative_difference(tinyad.hessian(i, j), autodiff.hessian(i, j))
          );
        }
      }
    }

    return stats;
  }

  /**
   * @brief Runs a generic timing loop.
   *
   * @tparam Evaluator callable evaluation routine.
   * @param samples benchmark points.
   * @param rounds number of full passes on the sample set.
   * @param evaluator evaluation routine.
   * @return TimingResult elapsed time and checksum.
   */
  template <typename Evaluator>
  TimingResult run_benchmark(
    std::vector<DenseVector> const& samples,
    int                            rounds,
    Evaluator const              & evaluator
  ) {
    using Clock = std::chrono::steady_clock;

    double checksum = 0.0;
    auto const start = Clock::now();

    for ( int round = 0; round < rounds; ++round ) {
      for ( DenseVector const & x : samples ) checksum += evaluator(x);
    }

    auto const stop = Clock::now();
    g_sink = checksum;

    TimingResult result;
    result.milliseconds =
      std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();
    result.checksum = checksum;
    return result;
  }

  /**
   * @brief Prints one benchmark row.
   *
   * @param label row label.
   * @param result timing result.
   * @param evaluations number of evaluations.
   * @param reference_ns reference cost per evaluation.
   */
  void print_benchmark_row(
    std::string const & label,
    TimingResult const& result,
    int                 evaluations,
    double              reference_ns
  ) {
    double const ns_per_eval = 1e6 * result.milliseconds / double(evaluations);

    std::cout
      << label
      << " | elapsed_ms " << result.milliseconds
      << " | ns_per_eval " << ns_per_eval
      << " | checksum " << result.checksum;

    if ( reference_ns > 0.0 ) std::cout << " | ratio_vs_tinyad " << (ns_per_eval / reference_ns);
    std::cout << '\n';
  }

  /**
   * @brief Benchmarks TinyAD and autodiff on two workloads.
   *
   * @tparam TinyFunction TinyAD function type.
   * @param tinyad_function TinyAD objective.
   */
  template <typename TinyFunction>
  void benchmark_tinyad_vs_autodiff( TinyFunction const & tinyad_function ) {
    std::cout << "\n== Timing comparison ==\n";

    std::array<TimingScenario, 2> const scenarios{{
      {"multivariate objective", 180, 120, 40},
      {"multivariate objective stress", 96, 240, 80}
    }};

    for ( TimingScenario const & scenario : scenarios ) {
      std::vector<DenseVector> const samples = build_samples(scenario.sample_count, 0.14);
      SweepStatistics const stats = compute_sweep_statistics(tinyad_function, samples);

      TimingResult const tinyad_gradient_time = run_benchmark(samples, scenario.gradient_rounds, [&] (DenseVector const & x) {
        GradientEvaluation const result = evaluate_tinyad_gradient(tinyad_function, x);
        return result.value + 1e-3 * result.gradient.squaredNorm();
      });

      TimingResult const autodiff_gradient_time = run_benchmark(samples, scenario.gradient_rounds, [&] (DenseVector const & x) {
        GradientEvaluation const result = evaluate_autodiff_gradient(x);
        return result.value + 1e-3 * result.gradient.squaredNorm();
      });

      TimingResult const tinyad_hessian_time = run_benchmark(samples, scenario.hessian_rounds, [&] (DenseVector const & x) {
        HessianEvaluation const result = evaluate_tinyad_hessian(tinyad_function, x);
        return result.value + 1e-3 * result.gradient.squaredNorm() + 1e-4 * result.hessian.diagonal().sum();
      });

      TimingResult const autodiff_hessian_time = run_benchmark(samples, scenario.hessian_rounds, [&] (DenseVector const & x) {
        HessianEvaluation const result = evaluate_autodiff_hessian(x);
        return result.value + 1e-3 * result.gradient.squaredNorm() + 1e-4 * result.hessian.diagonal().sum();
      });

      int const gradient_evaluations = scenario.sample_count * scenario.gradient_rounds;
      int const hessian_evaluations  = scenario.sample_count * scenario.hessian_rounds;

      double const tinyad_gradient_ns = 1e6 * tinyad_gradient_time.milliseconds / double(gradient_evaluations);
      double const tinyad_hessian_ns  = 1e6 * tinyad_hessian_time.milliseconds / double(hessian_evaluations);

      std::cout
        << "\nScenario: " << scenario.name
        << " | variables " << kVariableCount
        << " | samples " << scenario.sample_count
        << " | gradient rounds " << scenario.gradient_rounds
        << " | hessian rounds " << scenario.hessian_rounds
        << " | max_abs_gradient_diff " << stats.max_abs_gradient_diff
        << " | max_rel_gradient_diff " << stats.max_rel_gradient_diff
        << " | max_abs_hessian_diff " << stats.max_abs_hessian_diff
        << " | max_rel_hessian_diff " << stats.max_rel_hessian_diff
        << '\n';

      print_benchmark_row("TinyAD value+gradient", tinyad_gradient_time, gradient_evaluations, 0.0);
      print_benchmark_row("autodiff value+gradient", autodiff_gradient_time, gradient_evaluations, tinyad_gradient_ns);
      print_benchmark_row("TinyAD value+gradient+Hessian", tinyad_hessian_time, hessian_evaluations, 0.0);
      print_benchmark_row("autodiff value+gradient+Hessian", autodiff_hessian_time, hessian_evaluations, tinyad_hessian_ns);
    }
  }

  /**
   * @brief Executes detailed correctness checks at one sample point.
   *
   * @param ctx test context.
   * @param title section title.
   * @param tinyad TinyAD result.
   * @param autodiff autodiff result.
   */
  void compare_point_results(
    TestContext          & ctx,
    std::string const    & title,
    HessianEvaluation const& tinyad,
    HessianEvaluation const& autodiff
  ) {
    ctx.section(title);
    ctx.expect_close("objective value", tinyad.value, autodiff.value, 1e-11);

    for ( int i = 0; i < kVariableCount; ++i ) {
      ctx.expect_close(component_label("gradient", i), tinyad.gradient(i), autodiff.gradient(i), 1e-10);
    }

    for ( int i = 0; i < kVariableCount; ++i ) {
      for ( int j = i; j < kVariableCount; ++j ) {
        ctx.expect_close(matrix_label("hessian", i, j), tinyad.hessian(i, j), autodiff.hessian(i, j), 5e-10);
      }
    }
  }

} // namespace

int
main() {
  try {
    auto tinyad_function = build_tinyad_objective();

    TestContext ctx;

    DenseVector const point_a = build_sample_point(3, 0.09);
    DenseVector const point_b = build_sample_point(9, 0.14);

    HessianEvaluation const tinyad_a   = evaluate_tinyad_hessian(tinyad_function, point_a);
    HessianEvaluation const autodiff_a = evaluate_autodiff_hessian(point_a);
    HessianEvaluation const tinyad_b   = evaluate_tinyad_hessian(tinyad_function, point_b);
    HessianEvaluation const autodiff_b = evaluate_autodiff_hessian(point_b);

    compare_point_results(ctx, "Reference point A", tinyad_a, autodiff_a);
    compare_point_results(ctx, "Reference point B", tinyad_b, autodiff_b);

    ctx.section("Sweep statistics");
    std::vector<DenseVector> const sweep_samples = build_samples(14, 0.16);
    SweepStatistics const stats = compute_sweep_statistics(tinyad_function, sweep_samples);
    ctx.expect_close("max absolute gradient difference", stats.max_abs_gradient_diff, 0.0, 1e-10);
    ctx.expect_close("max relative gradient difference", stats.max_rel_gradient_diff, 0.0, 1e-12);
    ctx.expect_close("max absolute Hessian difference", stats.max_abs_hessian_diff, 0.0, 5e-10);
    ctx.expect_close("max relative Hessian difference", stats.max_rel_hessian_diff, 0.0, 1e-12);

    ctx.finalize();
    benchmark_tinyad_vs_autodiff(tinyad_function);
  } catch ( std::exception const & error ) {
    std::cerr << "\nFatal error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}
