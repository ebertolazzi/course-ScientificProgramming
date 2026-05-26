#include "dual.hh"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * @file test1.cc
 * @brief Verbose numerical tests for the `AD::Dual` class.
 */

namespace {

  //! Convenient alias for double-precision tests.
  using DUAL = AD::Dual<double>;

  /**
   * @brief Minimal context used to collect, print, and validate test checks.
   */
  struct TestContext {
    int total  = 0;
    int failed = 0;

    /**
     * @brief Prints a section header for a logical test group.
     *
     * @param title section title.
     */
    void section( std::string const & title ) const {
      std::cout << "\n== " << title << " ==\n";
    }

    /**
     * @brief Checks whether two scalars are close and prints a verbose line.
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
     * @brief Checks both the primal value and derivative of a dual number.
     *
     * @param label short description of the check.
     * @param actual computed dual result.
     * @param expected_value expected primal value.
     * @param expected_dual expected derivative.
     * @param tolerance absolute tolerance.
     */
    void expect_dual(
      std::string const & label,
      DUAL const        & actual,
      double              expected_value,
      double              expected_dual,
      double              tolerance = 1e-12
    ) {
      expect_close(label + " [value]", actual.value(), expected_value, tolerance);
      expect_close(label + " [dual]",  actual.dual(),  expected_dual,  tolerance);
    }

    /**
     * @brief Finishes the run and throws if at least one check failed.
     */
    void finalize() const {
      std::cout << "\nSummary: executed " << total << " checks";
      if ( failed == 0 ) {
        std::cout << ", all passed.\n";
        return;
      }
      std::cout << ", failures: " << failed << ".\n";
      throw std::runtime_error("dual tests failed");
    }
  };

  /**
   * @brief Builds an independent variable with unit derivative.
   *
   * @param x variable value.
   * @return DUAL corresponding dual variable.
   */
  DUAL variable( double x ) {
    return DUAL::variable(x);
  }

  /**
   * @brief Checks a unary function against expected value and derivative.
   *
   * @tparam DualFunction callable dual overload.
   * @tparam ScalarFunction callable scalar function.
   * @tparam DerivativeFunction callable scalar derivative.
   * @param ctx test context.
   * @param label test name.
   * @param x evaluation point.
   * @param dual_function function evaluated on dual numbers.
   * @param scalar_function scalar reference function.
   * @param derivative expected scalar derivative.
   * @param tolerance absolute tolerance.
   */
  template <typename DualFunction, typename ScalarFunction, typename DerivativeFunction>
  void check_unary(
    TestContext         & ctx,
    std::string const   & label,
    double                x,
    DualFunction const  & dual_function,
    ScalarFunction const& scalar_function,
    DerivativeFunction const & derivative,
    double                tolerance = 1e-12
  ) {
    DUAL const result = dual_function(variable(x));
    ctx.expect_dual(label, result, scalar_function(x), derivative(x), tolerance);
  }

  /**
   * @brief Checks a binary function with sensitivities on both arguments.
   *
   * @tparam DualFunction callable dual overload.
   * @tparam ScalarFunction callable scalar function.
   * @tparam DfdxFunction callable partial derivative with respect to `x`.
   * @tparam DfdyFunction callable partial derivative with respect to `y`.
   * @param ctx test context.
   * @param label test name.
   * @param x first argument value.
   * @param dx derivative carried by the first argument.
   * @param y second argument value.
   * @param dy derivative carried by the second argument.
   * @param dual_function function evaluated on dual numbers.
   * @param scalar_function scalar reference function.
   * @param dfdx scalar partial derivative with respect to `x`.
   * @param dfdy scalar partial derivative with respect to `y`.
   * @param tolerance absolute tolerance.
   */
  template <
    typename DualFunction,
    typename ScalarFunction,
    typename DfdxFunction,
    typename DfdyFunction
  >
  void check_binary(
    TestContext           & ctx,
    std::string const     & label,
    double                  x,
    double                  dx,
    double                  y,
    double                  dy,
    DualFunction const    & dual_function,
    ScalarFunction const  & scalar_function,
    DfdxFunction const    & dfdx,
    DfdyFunction const    & dfdy,
    double                  tolerance = 1e-12
  ) {
    DUAL const lhs(x, dx);
    DUAL const rhs(y, dy);
    DUAL const result = dual_function(lhs, rhs);
    double const expected_dual = dfdx(x, y) * dx + dfdy(x, y) * dy;
    ctx.expect_dual(label, result, scalar_function(x, y), expected_dual, tolerance);
  }

  /**
   * @brief Runs tests for constructors, assignments, and basic operators.
   *
   * @param ctx test context.
   */
  void test_basic_operations( TestContext & ctx ) {
    ctx.section("Basic operations");

    DUAL a;
    ctx.expect_dual("default constructor", a, 0.0, 0.0);

    DUAL b(2.5, -1.5);
    ctx.expect_dual("value constructor", b, 2.5, -1.5);

    DUAL c = DUAL::variable(4.0);
    ctx.expect_dual("variable constructor", c, 4.0, 1.0);

    c.set(-3.0, 7.0);
    ctx.expect_dual("set", c, -3.0, 7.0);

    c = 5.0;
    ctx.expect_dual("scalar assignment", c, 5.0, 0.0);

    DUAL const x(2.0, 3.0);
    DUAL const y(-1.5, 4.0);

    ctx.expect_dual("unary plus", +x, 2.0, 3.0);
    ctx.expect_dual("unary minus", -x, -2.0, -3.0);

    ctx.expect_dual("dual sum", x + y, 0.5, 7.0);
    ctx.expect_dual("scalar left sum", 1.25 + x, 3.25, 3.0);
    ctx.expect_dual("scalar right sum", x + 1.25, 3.25, 3.0);

    ctx.expect_dual("dual difference", x - y, 3.5, -1.0);
    ctx.expect_dual("scalar left difference", 1.25 - x, -0.75, -3.0);
    ctx.expect_dual("scalar right difference", x - 1.25, 0.75, 3.0);

    ctx.expect_dual("dual product", x * y, -3.0, 3.5);
    ctx.expect_dual("scalar left product", -2.0 * x, -4.0, -6.0);
    ctx.expect_dual("scalar right product", x * -2.0, -4.0, -6.0);

    ctx.expect_dual("dual quotient", x / y, -4.0 / 3.0, -50.0 / 9.0, 1e-11);
    ctx.expect_dual("scalar right quotient", x / 2.0, 1.0, 1.5);
    ctx.expect_dual("scalar left quotient", 6.0 / x, 3.0, -4.5);

    DUAL accum(1.0, 2.0);
    accum += DUAL(3.0, -4.0);
    ctx.expect_dual("operator +=", accum, 4.0, -2.0);
    accum += 2.0;
    ctx.expect_dual("operator += scalar", accum, 6.0, -2.0);
    accum -= DUAL(1.0, 3.0);
    ctx.expect_dual("operator -=", accum, 5.0, -5.0);
    accum -= 4.0;
    ctx.expect_dual("operator -= scalar", accum, 1.0, -5.0);
    accum *= DUAL(-2.0, 1.0);
    ctx.expect_dual("operator *=", accum, -2.0, 11.0);
    accum *= -0.5;
    ctx.expect_dual("operator *= scalar", accum, 1.0, -5.5);
    accum /= DUAL(4.0, -2.0);
    ctx.expect_dual("operator /=", accum, 0.25, -1.25);
    accum /= 0.5;
    ctx.expect_dual("operator /= scalar", accum, 0.5, -2.5);

    ctx.expect_close("operator == with scalar", (DUAL(3.0, 0.0) == 3.0) ? 1.0 : 0.0, 1.0);
    ctx.expect_close("operator != with dual", (DUAL(3.0, 1.0) != DUAL(3.0, 0.0)) ? 1.0 : 0.0, 1.0);

    std::ostringstream out;
    out << DUAL(-1.5, 2.25);
    ctx.expect_close("stream output is not empty", out.str().empty() ? 0.0 : 1.0, 1.0);
  }

  /**
   * @brief Runs tests for trigonometric and inverse trigonometric functions.
   *
   * @param ctx test context.
   */
  void test_trigonometric_functions( TestContext & ctx ) {
    ctx.section("Trigonometric functions");

    check_unary(ctx, "sin", 0.3, AD::sin<double>, []( double x ) { return std::sin(x); }, []( double x ) {
      return std::cos(x);
    });
    check_unary(ctx, "cos", 0.3, AD::cos<double>, []( double x ) { return std::cos(x); }, []( double x ) {
      return -std::sin(x);
    });
    check_unary(ctx, "tan", 0.3, AD::tan<double>, []( double x ) { return std::tan(x); }, []( double x ) {
      double const c = std::cos(x);
      return 1.0 / (c * c);
    });
    check_unary(ctx, "asin", 0.2, AD::asin<double>, []( double x ) { return std::asin(x); }, []( double x ) {
      return 1.0 / std::sqrt(1.0 - x * x);
    });
    check_unary(ctx, "acos", 0.2, AD::acos<double>, []( double x ) { return std::acos(x); }, []( double x ) {
      return -1.0 / std::sqrt(1.0 - x * x);
    });
    check_unary(ctx, "atan", 0.7, AD::atan<double>, []( double x ) { return std::atan(x); }, []( double x ) {
      return 1.0 / (1.0 + x * x);
    });

    check_binary(
      ctx, "atan2", 0.7, 1.5, 1.2, -0.5,
      []( DUAL const & y, DUAL const & x ) { return AD::atan2(y, x); },
      []( double y, double x ) { return std::atan2(y, x); },
      []( double y, double x ) { return x / (x * x + y * y); },
      []( double y, double x ) { return -y / (x * x + y * y); }
    );
  }

  /**
   * @brief Runs tests for hyperbolic and inverse hyperbolic functions.
   *
   * @param ctx test context.
   */
  void test_hyperbolic_functions( TestContext & ctx ) {
    ctx.section("Hyperbolic functions");

    check_unary(ctx, "sinh", 0.4, AD::sinh<double>, []( double x ) { return std::sinh(x); }, []( double x ) {
      return std::cosh(x);
    });
    check_unary(ctx, "cosh", 0.4, AD::cosh<double>, []( double x ) { return std::cosh(x); }, []( double x ) {
      return std::sinh(x);
    });
    check_unary(ctx, "tanh", 0.4, AD::tanh<double>, []( double x ) { return std::tanh(x); }, []( double x ) {
      double const c = std::cosh(x);
      return 1.0 / (c * c);
    });
    check_unary(ctx, "asinh", -0.6, AD::asinh<double>, []( double x ) { return std::asinh(x); }, []( double x ) {
      return 1.0 / std::sqrt(x * x + 1.0);
    });
    check_unary(ctx, "acosh", 1.7, AD::acosh<double>, []( double x ) { return std::acosh(x); }, []( double x ) {
      return 1.0 / (std::sqrt(x - 1.0) * std::sqrt(x + 1.0));
    });
    check_unary(ctx, "atanh", 0.25, AD::atanh<double>, []( double x ) { return std::atanh(x); }, []( double x ) {
      return 1.0 / (1.0 - x * x);
    });
  }

  /**
   * @brief Runs tests for exponential and logarithmic functions.
   *
   * @param ctx test context.
   */
  void test_exponential_and_logarithmic_functions( TestContext & ctx ) {
    ctx.section("Exponential and logarithmic functions");

    check_unary(ctx, "exp", 0.45, AD::exp<double>, []( double x ) { return std::exp(x); }, []( double x ) {
      return std::exp(x);
    });
    check_unary(ctx, "exp2", 0.45, AD::exp2<double>, []( double x ) { return std::exp2(x); }, []( double x ) {
      return std::exp2(x) * std::log(2.0);
    });
    check_unary(ctx, "expm1", 0.45, AD::expm1<double>, []( double x ) { return std::expm1(x); }, []( double x ) {
      return std::exp(x);
    });
    check_unary(ctx, "log", 1.8, AD::log<double>, []( double x ) { return std::log(x); }, []( double x ) {
      return 1.0 / x;
    });
    check_unary(ctx, "log2", 1.8, AD::log2<double>, []( double x ) { return std::log2(x); }, []( double x ) {
      return 1.0 / (x * std::log(2.0));
    });
    check_unary(ctx, "log10", 1.8, AD::log10<double>, []( double x ) { return std::log10(x); }, []( double x ) {
      return 1.0 / (x * std::log(10.0));
    });
    check_unary(ctx, "log1p", 0.35, AD::log1p<double>, []( double x ) { return std::log1p(x); }, []( double x ) {
      return 1.0 / (1.0 + x);
    });
  }

  /**
   * @brief Runs tests for powers, roots, and related functions.
   *
   * @param ctx test context.
   */
  void test_power_and_root_functions( TestContext & ctx ) {
    ctx.section("Power and root functions");

    check_unary(ctx, "sqrt", 2.25, AD::sqrt<double>, []( double x ) { return std::sqrt(x); }, []( double x ) {
      return 1.0 / (2.0 * std::sqrt(x));
    });
    check_unary(ctx, "cbrt", 1.7, AD::cbrt<double>, []( double x ) { return std::cbrt(x); }, []( double x ) {
      double const r = std::cbrt(x);
      return 1.0 / (3.0 * r * r);
    });

    check_binary(
      ctx, "pow dual-dual", 1.8, 0.7, 1.2, -0.4,
      []( DUAL const & x, DUAL const & y ) { return AD::pow(x, y); },
      []( double x, double y ) { return std::pow(x, y); },
      []( double x, double y ) { return y * std::pow(x, y - 1.0); },
      []( double x, double y ) { return std::pow(x, y) * std::log(x); },
      2e-12
    );

    DUAL const a(1.8, 0.7);
    DUAL const b = AD::pow(a, 2.5);
    ctx.expect_dual(
      "pow dual-scalar",
      b,
      std::pow(1.8, 2.5),
      2.5 * std::pow(1.8, 1.5) * 0.7,
      2e-12
    );

    DUAL const c = AD::pow(2.5, DUAL(0.4, -1.2));
    ctx.expect_dual(
      "pow scalar-dual",
      c,
      std::pow(2.5, 0.4),
      std::pow(2.5, 0.4) * std::log(2.5) * -1.2,
      2e-12
    );

    DUAL const h = AD::hypot(DUAL(3.0, 1.5), DUAL(4.0, -2.0));
    ctx.expect_dual("hypot", h, 5.0, (3.0 * 1.5 + 4.0 * -2.0) / 5.0);

    DUAL const e = AD::fma(DUAL(2.0, 3.0), DUAL(-1.0, 4.0), DUAL(5.0, -2.0));
    ctx.expect_dual("fma", e, 3.0, 3.0);
  }

  /**
   * @brief Runs tests for auxiliary and special functions.
   *
   * @param ctx test context.
   */
  void test_auxiliary_functions( TestContext & ctx ) {
    ctx.section("Auxiliary and special functions");

    check_unary(ctx, "abs negative", -2.4, AD::abs<double>, []( double x ) {
      return std::abs(x);
    }, []( double ) {
      return -1.0;
    });

    check_unary(ctx, "floor", 3.8, AD::floor<double>, []( double x ) {
      return std::floor(x);
    }, []( double ) {
      return 0.0;
    });
    check_unary(ctx, "ceil", 3.2, AD::ceil<double>, []( double x ) {
      return std::ceil(x);
    }, []( double ) {
      return 0.0;
    });
    check_unary(ctx, "trunc", -3.8, AD::trunc<double>, []( double x ) {
      return std::trunc(x);
    }, []( double ) {
      return 0.0;
    });
    check_unary(ctx, "round", 3.2, AD::round<double>, []( double x ) {
      return std::round(x);
    }, []( double ) {
      return 0.0;
    });

    check_unary(ctx, "erf", 0.4, AD::erf<double>, []( double x ) {
      return std::erf(x);
    }, []( double x ) {
      return 2.0 / std::sqrt(std::acos(-1.0)) * std::exp(-x * x);
    }, 2e-12);

    check_unary(ctx, "erfc", 0.4, AD::erfc<double>, []( double x ) {
      return std::erfc(x);
    }, []( double x ) {
      return -2.0 / std::sqrt(std::acos(-1.0)) * std::exp(-x * x);
    }, 2e-12);

    DUAL const scaled = AD::ldexp(DUAL(0.75, -2.0), 3);
    ctx.expect_dual("ldexp", scaled, std::ldexp(0.75, 3), std::ldexp(-2.0, 3));

    DUAL const scalbn_value = AD::scalbn(DUAL(0.75, -2.0), 2);
    ctx.expect_dual("scalbn", scalbn_value, std::scalbn(0.75, 2), std::scalbn(-2.0, 2));

    DUAL const scalbln_value = AD::scalbln(DUAL(0.75, -2.0), 2L);
    ctx.expect_dual(
      "scalbln",
      scalbln_value,
      std::scalbln(0.75, 2L),
      std::scalbln(-2.0, 2L)
    );
  }

  /**
   * @brief Runs a non-trivial composed-expression test.
   *
   * @param ctx test context.
   */
  void test_composed_expression( TestContext & ctx ) {
    ctx.section("Composed expression");

    auto const function = []( DUAL const & x ) {
      using AD::cos;
      using AD::exp;
      using AD::log1p;
      using AD::sin;
      return (x * x + 2.0 * x + 1.0) * exp(sin(x)) / log1p(x) + cos(x);
    };

    double const x = 0.4;
    DUAL const result = function(variable(x));

    double const value =
      ((x * x + 2.0 * x + 1.0) * std::exp(std::sin(x)) / std::log1p(x)) +
      std::cos(x);

    double const deriv =
      ((2.0 * x + 2.0) * std::exp(std::sin(x)) +
       (x * x + 2.0 * x + 1.0) * std::exp(std::sin(x)) * std::cos(x))
      / std::log1p(x)
      - (x * x + 2.0 * x + 1.0) * std::exp(std::sin(x))
      / (std::log1p(x) * std::log1p(x) * (1.0 + x))
      - std::sin(x);

    ctx.expect_dual("composed expression", result, value, deriv, 5e-12);
  }

}

/**
 * @brief Entry point of the test program.
 *
 * @return int exit code `0` on success.
 */
int main() {
  try {
    TestContext ctx;
    test_basic_operations(ctx);
    test_trigonometric_functions(ctx);
    test_hyperbolic_functions(ctx);
    test_exponential_and_logarithmic_functions(ctx);
    test_power_and_root_functions(ctx);
    test_auxiliary_functions(ctx);
    test_composed_expression(ctx);
    ctx.finalize();
  } catch ( std::exception const & exc ) {
    std::cerr << exc.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
