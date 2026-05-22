#include "exercize3.hh"

namespace Exercize3 {

  namespace {

    using clock_type = std::chrono::steady_clock;

    clock_type::time_point g_tic = clock_type::now();

    /**
     * @brief Print a one-line explanation inside the running lesson.
     * @param text Comment printed after a section title or a matrix.
     */
    void
    print_note( std::string const & text ) {
      fmt::print(fg(fmt::color::light_steel_blue), "{}\n\n", text);
    }

  }

  void
  tic() {
    g_tic = clock_type::now();
  }

  real_type
  toc() {
    auto const elapsed =
      std::chrono::duration_cast<std::chrono::duration<real_type,std::milli>>
        ( clock_type::now() - g_tic );
    return elapsed.count();
  }

  mat_type
  make_reference_matrix() {
    mat_type A( 3, 10 );
    A << 1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
         21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
         31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    return A;
  }

  void
  print_section( std::string const & title ) {
    fmt::print(
      fg(fmt::color::yellow_green) | fmt::emphasis::bold,
      "\n=== {} ===\n\n",
      title
    );
  }

  /**
   * @brief Lesson 1: blocks and corner views.
   *
   * @details
   * `topLeftCorner`, `block`, `leftCols`, `rightCols`, and `middleCols`
   * return Eigen expressions that refer to the original coefficients.
   * No allocation is performed and changes are reflected immediately in
   * the source matrix.
   */
  void
  lesson_standard_views() {
    print_section( "Lesson 1 - standard Eigen views" );

    mat_type A = make_reference_matrix();
    print_matrix( "Starting matrix A:", A );

    auto TL = A.topLeftCorner( 2, 2 );
    print_note(
      "topLeftCorner(2,2) returns a view: it modifies the block, not a copy."
    );
    print_matrix( "View TL = A.topLeftCorner(2,2):", TL );

    TL *= 10.0;
    print_matrix( "TL after TL *= 10:", TL );
    print_matrix( "A after modifying the view:", A );

    auto LAST   = A.rightCols( 2 );
    auto FIRST  = A.leftCols( 2 );
    auto MIDDLE = A.middleCols( 2, 4 );

    print_note(
      "leftCols, rightCols, and middleCols are convenient views for contiguous slices."
    );
    print_matrix( "FIRST = A.leftCols(2):", FIRST );
    print_matrix( "MIDDLE = A.middleCols(2,4):", MIDDLE );
    print_matrix( "LAST = A.rightCols(2):", LAST );
  }

  /**
   * @brief Lesson 2: a raw map follows memory contiguity, not matrix geometry.
   *
   * @details
   * In a column-major matrix, `A.data()` starts from the first column.
   * Therefore `Eigen::Map<mat_type>(A.data(),2,2)` reads the first four
   * contiguous coefficients:
   * `1, 21, 31, 2`.
   * This explains why the result is different from `A.topLeftCorner(2,2)`.
   */
  void
  lesson_basic_map() {
    print_section( "Lesson 2 - Eigen::Map on contiguous memory" );

    mat_type A = make_reference_matrix();
    print_matrix( "Starting matrix A:", A );

    auto TL = A.topLeftCorner( 2, 2 );
    Eigen::Map<mat_type> raw_map( A.data(), 2, 2 );

    print_note(
      "Map reads contiguous data starting from A.data(); it does not know the logical shape of the block."
    );
    print_matrix( "Logical view TL = A.topLeftCorner(2,2):", TL );
    print_matrix( "Map raw_map(A.data(),2,2):", raw_map );
  }

  /**
   * @brief Lesson 3: use `OuterStride` to recover a logical block.
   *
   * @details
   * The top-left `2 x 2` block of a `3 x 10` column-major matrix is not
   * contiguous because the third row sits between the two columns in memory.
   * The correct stride is `A.outerStride()`, which for this matrix is `3`.
   *
   * @code
   * Eigen::Map<mat_type, 0, Eigen::OuterStride<>>
   *   logical_block(A.data(), 2, 2, Eigen::OuterStride<>(A.outerStride()));
   * @endcode
   *
   * Mutating the map still mutates the original matrix because the map is a
   * view on external memory.
   */
  void
  lesson_strided_map() {
    print_section( "Lesson 3 - Eigen::Map with stride" );

    mat_type A = make_reference_matrix();
    auto TL = A.topLeftCorner( 2, 2 );

    Eigen::Map<mat_type,0,Eigen::OuterStride<>>
      logical_block( A.data(), 2, 2, Eigen::OuterStride<>(A.outerStride()) );

    print_note(
      "OuterStride describes the distance between the start of two consecutive columns in the original memory layout."
    );
    print_matrix( "Logical view TL = A.topLeftCorner(2,2):", TL );
    print_matrix( "Map with the correct stride:", logical_block );

    logical_block += mat_type::Constant( 2, 2, 100.0 );
    print_matrix( "Map after adding 100 to each coefficient:", logical_block );
    print_matrix( "A updated through the Map:", A );
  }

  /**
   * @brief Lesson 4: rebuild maps in place with placement new.
   *
   * @details
   * This pattern appears when a lesson wants to create an empty placeholder
   * `Map` and later bind it to different contiguous column blocks. The
   * underlying matrix is still shared, so algebra on the maps updates the
   * source matrix immediately.
   */
  void
  lesson_placement_new_map() {
    print_section( "Lesson 4 - rebinding Eigen::Map with placement new" );

    mat_type A = make_reference_matrix();

    auto FIRST  = A.leftCols( 2 );
    auto MIDDLE = A.middleCols( 2, 4 );
    auto LAST   = A.rightCols( 2 );

    Eigen::Map<mat_type> left_map  { nullptr, 0, 0 };
    Eigen::Map<mat_type> mid_map   { nullptr, 0, 0 };
    Eigen::Map<mat_type> right_map { nullptr, 0, 0 };

    print_note(
      "Placement new reconstructs each Map object in place so it can be rebound to a new memory region and shape."
    );

    new (&left_map)  Eigen::Map<mat_type>( FIRST.data(),  3, 2 );
    new (&mid_map)   Eigen::Map<mat_type>( MIDDLE.data(), 3, 4 );
    new (&right_map) Eigen::Map<mat_type>( LAST.data(),   3, 2 );

    print_matrix( "FIRST = A.leftCols(2):", FIRST );
    print_matrix( "left_map rebound with placement new:", left_map );
    print_matrix( "MIDDLE = A.middleCols(2,4):", MIDDLE );
    print_matrix( "mid_map rebound with placement new:", mid_map );
    print_matrix( "LAST = A.rightCols(2):", LAST );
    print_matrix( "right_map rebound with placement new:", right_map );

    print_note(
      "Because the three maps are views, right_map += left_map updates the last two columns of A in place."
    );
    print_matrix( "A before right_map += left_map:", A );
    right_map += left_map;
    print_matrix( "A after right_map += left_map:", A );
  }

  /**
   * @brief Lesson 5: advanced slicing with Eigen's indexing module.
   *
   * @details
   * `seq(first,last,step)` creates arithmetic progressions of indices.
   * Combined with `all` and `last`, it becomes easy to express patterns such
   * as odd or even columns without manually building index vectors.
   */
  void
  lesson_slices() {
    print_section( "Lesson 5 - slices with seq, all, and last" );

    using namespace Eigen::indexing;

    mat_type A = make_reference_matrix();
    auto odd_columns  = seq( 0, last, 2 );
    auto even_columns = seq( 1, last, 2 );
    auto top_rows     = seq( 0, 1 );

    print_note(
      "Slices built with seq let you select regular patterns without writing explicit loops."
    );
    print_matrix( "A(:, seq(0,last,2)) -> odd columns in C++ indexing:", A( all, odd_columns ) );
    print_matrix( "A(:, seq(1,last,2)) -> even columns in C++ indexing:", A( all, even_columns ) );
    print_matrix( "A(seq(0,1), all) -> first two rows:", A( top_rows, all ) );
  }

  /**
   * @brief Lesson 6: slice expressions can be assigned in place.
   *
   * @details
   * The left-hand side and the right-hand side are both expressions.
   * This is a compact way to rewrite regular patterns across a matrix.
   */
  void
  lesson_slice_assignment() {
    print_section( "Lesson 6 - assignment between slices" );

    using namespace Eigen::indexing;

    mat_type A = make_reference_matrix();
    auto odd_columns  = seq( 0, last, 2 );
    auto even_columns = seq( 1, last, 2 );

    print_matrix( "A before the assignment:", A );
    print_note(
      "Here we overwrite columns with index 0,2,4,... using columns with index 1,3,5,...."
    );

    A( all, odd_columns ) = A( all, even_columns );
    print_matrix( "A after A(all, odd_columns) = A(all, even_columns):", A );
  }

}

int
main() {
  using namespace Exercize3;

  tic();
  lesson_standard_views();
  lesson_basic_map();
  lesson_strided_map();
  lesson_placement_new_map();
  lesson_slices();
  lesson_slice_assignment();

  fmt::print(
    fg(fmt::color::orange) | fmt::emphasis::bold,
    "Lesson completed in {:.3f} ms\n",
    toc()
  );

  return 0;
}
