/*
 * {FMT} LIBRARY COMPLETE LESSON - FIXED FOR fmt >= 11.0
 * =====================================================
 * All custom formatter::format() methods are now marked const.
 * This is required by {fmt} version 11.0 and later.
 */

#include "fmt_lesson.h"

// ============================================================================
// Custom types for Module 5
// ============================================================================
struct Point2D {
    double x, y;
    double magnitude() const { return std::sqrt(x*x + y*y); }
};

struct RGB {
    uint8_t r, g, b;
};

class Person {
    std::string name;
    int age;
public:
    Person(std::string n, int a) : name(std::move(n)), age(a) {}
    const std::string& get_name() const { return name; }
    int get_age() const { return age; }
};

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

// ============================================================================
// Formatter specializations - ALL format() methods marked const
// ============================================================================

// Formatter for Point2D
template <> struct fmt::formatter<Point2D> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    // FIXED: format() is const
    template <typename FormatContext>
    auto format(const Point2D& p, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "Point({:.2f}, {:.2f})", p.x, p.y);
    }
};

// Formatter for RGB with optional color output
template <> struct fmt::formatter<RGB> {
    bool colored = false;
    
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin();
        if (it != ctx.end() && *it == 'c') { colored = true; ++it; }
        return it;
    }
    
    // FIXED: format() is const
    template <typename FormatContext>
    auto format(const RGB& rgb, FormatContext& ctx) const {
        if (colored)
            return fmt::format_to(ctx.out(), fg(fmt::rgb(rgb.r, rgb.g, rgb.b)),
                                  "RGB({}, {}, {})", rgb.r, rgb.g, rgb.b);
        return fmt::format_to(ctx.out(), "RGB({}, {}, {})", rgb.r, rgb.g, rgb.b);
    }
};

// Formatter for Person
template <> struct fmt::formatter<Person> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    // FIXED: format() is const
    template <typename FormatContext>
    auto format(const Person& p, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "Person(name='{}', age={})",
                              p.get_name(), p.get_age());
    }
};

// Formatter for LogLevel with colors
template <> struct fmt::formatter<LogLevel> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    // FIXED: format() is const
    template <typename FormatContext>
    auto format(LogLevel level, FormatContext& ctx) const {
        std::string_view name;
        fmt::color color;
        switch (level) {
            case LogLevel::DEBUG:    name = "DEBUG";    color = fmt::color::white;   break;
            case LogLevel::INFO:     name = "INFO";     color = fmt::color::green;   break;
            case LogLevel::WARNING:  name = "WARNING";  color = fmt::color::yellow;  break;
            case LogLevel::ERROR:    name = "ERROR";    color = fmt::color::red;     break;
            case LogLevel::CRITICAL: name = "CRITICAL"; color = fmt::color::red;     break;
        }
        return fmt::format_to(ctx.out(), fmt::emphasis::bold | fg(color), "{}", name);
    }
};

// ============================================================================
// Utility: Timer class for Module 6
// ============================================================================
class Timer {
    std::chrono::high_resolution_clock::time_point start;
    std::string name;
public:
    Timer(std::string n)
    : start(std::chrono::high_resolution_clock::now())
    , name(std::move(n)) {}
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        fmt::print(fg(fmt::color::cyan), "  {}: {} μs\n", name, dur.count());
    }
};

// ============================================================================
// MAIN
// ============================================================================
int main() {
    // Header
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan),
               "\n╔══════════════════════════════════════════════════════════════╗\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan),
               "║         {{fmt}} LIBRARY COMPLETE LESSON - C++17              ║\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan),
               "╚══════════════════════════════════════════════════════════════╝\n");
    
    fmt::print(fg(fmt::color::yellow), 
               "\n📚 Modern formatting library (std::format in C++20)\n\n");
    
    print_section("MODULE 1: BASIC FORMATTING");
    demo_basic_formatting();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    print_section("MODULE 2: COLORS AND STYLES");
    demo_colors_styles();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    print_section("MODULE 3: ADVANCED FORMATTING");
    demo_advanced_formatting();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    print_section("MODULE 4: CHRONO FORMATTING");
    demo_chrono_formatting();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    print_section("MODULE 5: CUSTOM TYPES");
    demo_custom_types();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    print_section("MODULE 6: PERFORMANCE TIPS");
    demo_performance_tips();
    
    // Summary
    print_section("LESSON SUMMARY");
    fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "\n✅ Key Takeaways:\n\n");
    fmt::print("  1. {{fmt}} is type-safe - compile-time format string checking\n");
    fmt::print("  2. Python-like syntax with {{}} placeholders\n");
    fmt::print("  3. Colors: 16 colors + 24-bit RGB + text styles\n");
    fmt::print("  4. Chrono formatting for durations and time points\n");
    fmt::print("  5. Custom types via formatter specialization (const format!)\n");
    fmt::print("  6. format_to() with buffers for high performance\n");
    fmt::print("  7. Container formatting with fmt::join()\n");
    fmt::print("  8. Adopted as std::format in C++20\n");
    
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan),
               "\n╔══════════════════════════════════════════════════════════════╗\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan),
               "║               END OF {{fmt}} LESSON                         ║\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan),
               "╚══════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}

// ============================================================================
// MODULE 1: BASIC FORMATTING
// ============================================================================
void demo_basic_formatting() {
    fmt::print(fg(fmt::color::yellow), 
               "\n┌─────────────────────────────────────────────────────────────┐\n");
    fmt::print(fg(fmt::color::yellow), 
               "│ BASIC FORMATTING: format(), print(), specifiers            │\n");
    fmt::print(fg(fmt::color::yellow), 
               "└─────────────────────────────────────────────────────────────┘\n\n");
    
    // Simple formatting
    fmt::print("--- Simple Formatting ---\n");
    std::string result = fmt::format("Hello, {}!", "World");
    fmt::print("format(): {}\n", result);
    fmt::print("print():  Hello, {}!\n", "World");
    fmt::print("Multiple: {}, {}, {}\n", 1, 2.5, "three");
    
    // Positional arguments
    fmt::print("\n--- Positional Arguments ---\n");
    fmt::print("{1} {0} {2}\n", "World", "Hello", "!");
    fmt::print("{0} + {1} = {2}\n", 10, 20, 30);
    fmt::print("Repeat: {0}{0}{1}{1}\n", "Ha", "!");
    
    // Integer formatting
    fmt::print("\n--- Integer Formatting ---\n");
    int num = 255;
    fmt::print("Decimal:     {:d}\n", num);
    fmt::print("Hex:         {:x}\n", num);
    fmt::print("Hex upper:   {:X}\n", num);
    fmt::print("Octal:       {:o}\n", num);
    fmt::print("Binary:      {:b}\n", num);
    fmt::print("Binary 8bit: {:08b}\n", num);
    fmt::print("Thousands:   {:L}\n", 1000000);
    
    // Floating point
    fmt::print("\n--- Floating Point Formatting ---\n");
    double pi = 3.14159265359;
    fmt::print("Default:     {}\n", pi);
    fmt::print("Fixed 2:     {:.2f}\n", pi);
    fmt::print("Scientific:  {:.3e}\n", pi);
    fmt::print("General:     {:.3g}\n", pi);
    fmt::print("Hex float:   {:a}\n", pi);
    
    // Width and alignment
    fmt::print("\n--- Width and Alignment ---\n");
    fmt::print("Right:  |{:>10}|\n", "hello");
    fmt::print("Left:   |{:<10}|\n", "hello");
    fmt::print("Center: |{:^10}|\n", "hello");
    fmt::print("Fill:   |{:*^20}|\n", "CENTER");
    fmt::print("Zero:   |{:0>5}|\n", 42);
    
    // Sign formatting
    fmt::print("\n--- Sign Formatting ---\n");
    fmt::print("Show sign:  {:+}\n", 42);
    fmt::print("Negative:   {:+}\n", -42);
    fmt::print("Space sign: {: }\n", 42);
    
    // String formatting
    fmt::print("\n--- String Formatting ---\n");
    std::string text = "Hello World";
    fmt::print("Truncate:  {:.5}\n", text);
    fmt::print("Pad right: |{:20.10}|\n", text);
    
    // Special types
    fmt::print("\n--- Special Types ---\n");
    fmt::print("Boolean: {} {}\n", true, false);
    fmt::print("Pointer: {}\n", fmt::ptr(&text));
    
    // Escaping braces
    fmt::print("\n--- Escaping Braces ---\n");
    fmt::print("Literal braces: {{Hello}}\n");
    
    // Named arguments
    fmt::print("\n--- Named Arguments ---\n");
    fmt::print("{name} is {age} years old\n", 
               fmt::arg("name", "Alice"), 
               fmt::arg("age", 30));
    
    // Output targets
    fmt::print("\n--- Output Targets ---\n");
    fmt::print(stderr, "This goes to stderr\n");
    char buffer[100];
    auto end = fmt::format_to(buffer, "Buffer: {}\n", "test");
    *end = '\0';
    fmt::print("Buffer output: {}", buffer);
}

// ============================================================================
// MODULE 2: COLORS AND STYLES
// ============================================================================
void demo_colors_styles() {
    fmt::print(fg(fmt::color::yellow), 
               "\n┌─────────────────────────────────────────────────────────────┐\n");
    fmt::print(fg(fmt::color::yellow), 
               "│ COLORS & STYLES: text colors, backgrounds, RGB, emphasis    │\n");
    fmt::print(fg(fmt::color::yellow), 
               "└─────────────────────────────────────────────────────────────┘\n\n");
    
    // Basic text colors
    fmt::print("--- Basic Text Colors ---\n");
    fmt::print(fg(fmt::color::red),     "Red text\n");
    fmt::print(fg(fmt::color::green),   "Green text\n");
    fmt::print(fg(fmt::color::blue),    "Blue text\n");
    fmt::print(fg(fmt::color::yellow),  "Yellow text\n");
    fmt::print(fg(fmt::color::cyan),    "Cyan text\n");
    fmt::print(fg(fmt::color::magenta), "Magenta text\n");
    fmt::print(fg(fmt::color::white),   "White text\n");
    
    // Bright colors
    fmt::print("\n--- Bright Colors ---\n");
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "Bright red\n");
    fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "Bright green\n");
    fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, "Bright blue\n");
    
    // Background colors
    fmt::print("\n--- Background Colors ---\n");
    fmt::print(bg(fmt::color::red), "Red background\n");
    fmt::print(bg(fmt::color::green) | fg(fmt::color::white), "Green bg, white fg\n");
    fmt::print(bg(fmt::color::blue) | fg(fmt::color::white), "Blue bg, white fg\n");
    fmt::print(bg(fmt::color::yellow) | fg(fmt::color::black), "Yellow bg, black fg\n");
    
    // Text styles
    fmt::print("\n--- Text Styles ---\n");
    fmt::print(fmt::emphasis::bold, "Bold text\n");
    fmt::print(fmt::emphasis::italic, "Italic text\n");
    fmt::print(fmt::emphasis::underline, "Underlined text\n");
    fmt::print(fmt::emphasis::strikethrough, "Strikethrough text\n");
    fmt::print(fmt::emphasis::faint, "Faint/dim text\n");
    
    // Combined styles
    fmt::print("\n--- Combined Styles ---\n");
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "Bold red text\n");
    fmt::print(fg(fmt::color::green) | bg(fmt::color::black) | 
               fmt::emphasis::underline, "Green underlined on black\n");
    fmt::print(fmt::emphasis::bold | fmt::emphasis::italic | 
               fg(fmt::color::cyan), "Bold italic cyan\n");
    
    // RGB colors
    fmt::print("\n--- RGB Colors (24-bit) ---\n");
    fmt::print(fg(fmt::rgb(255, 0, 0)), "Pure red (255,0,0)\n");
    fmt::print(fg(fmt::rgb(0, 255, 0)), "Pure green (0,255,0)\n");
    fmt::print(fg(fmt::rgb(0, 0, 255)), "Pure blue (0,0,255)\n");
    fmt::print(fg(fmt::rgb(255, 165, 0)), "Orange (255,165,0)\n");
    fmt::print(fg(fmt::rgb(128, 0, 128)), "Purple (128,0,128)\n");
    fmt::print(fg(fmt::rgb(0, 255, 255)), "Cyan RGB (0,255,255)\n");
    fmt::print(bg(fmt::rgb(255, 200, 0)) | fg(fmt::color::black), 
               "Gold background\n");
    
    // Color gradient
    fmt::print("\n--- Color Gradient ---\n");
    for (int i = 0; i < 256; i += 25) {
        fmt::print(fg(fmt::rgb(i, 0, 255 - i)), "█");
    }
    fmt::print("\n");
    for (int i = 0; i < 256; i += 25) {
        fmt::print(fg(fmt::rgb(255 - i, i, 0)), "█");
    }
    fmt::print("\n");
    
    // Practical log messages
    fmt::print("\n--- Practical Log Messages ---\n");
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "❌ ERROR: File not found\n");
    fmt::print(fg(fmt::color::yellow), "⚠️  WARNING: Low disk space\n");
    fmt::print(fg(fmt::color::green), "✅ SUCCESS: Operation completed\n");
    fmt::print(fg(fmt::color::cyan), "ℹ️  INFO: Processing file...\n");
    fmt::print(fg(fmt::color::magenta) | fmt::emphasis::faint, "🐛 DEBUG: Variable x = 42\n");
    
    // Colored table
    fmt::print("\n--- Colored Table ---\n");
    fmt::print(bg(fmt::color::blue) | fg(fmt::color::white) | fmt::emphasis::bold,
               " {:<20} | {:>10} | {:>10} \n", "Name", "Score", "Grade");
    fmt::print("{:-<47}\n", "");
    fmt::print(fg(fmt::color::green),  " {:<20} | {:>10} | {:>10} \n", "Alice", 95, "A");
    fmt::print(fg(fmt::color::cyan),   " {:<20} | {:>10} | {:>10} \n", "Bob", 87, "B+");
    fmt::print(fg(fmt::color::yellow), " {:<20} | {:>10} | {:>10} \n", "Charlie", 76, "B");
    fmt::print(fg(fmt::color::red),    " {:<20} | {:>10} | {:>10} \n", "David", 62, "C-");
}

// ============================================================================
// MODULE 3: ADVANCED FORMATTING
// ============================================================================
void demo_advanced_formatting() {
    fmt::print(fg(fmt::color::yellow), 
               "\n┌─────────────────────────────────────────────────────────────┐\n");
    fmt::print(fg(fmt::color::yellow), 
               "│ ADVANCED FORMATTING: ranges, tuples, join(), tables         │\n");
    fmt::print(fg(fmt::color::yellow), 
               "└─────────────────────────────────────────────────────────────┘\n\n");
    
    // Container formatting
    fmt::print("--- Container Formatting ---\n");
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
    
    fmt::print("Vector: {}\n", numbers);
    fmt::print("Strings: {}\n", names);
    fmt::print("Map: {}\n", ages);
    
    // Pair and tuple
    fmt::print("\n--- Pair and Tuple ---\n");
    std::pair<int, double> pair{42, 3.14};
    std::tuple<int, std::string, double> tuple{1, "hello", 2.718};
    fmt::print("Pair: {}\n", pair);
    fmt::print("Tuple: {}\n", tuple);
    
    // Dynamic width/precision
    fmt::print("\n--- Dynamic Width/Precision ---\n");
    for (int w = 1; w <= 5; ++w)
        fmt::print("{:>{}}\n", "X", w);
    for (int p = 1; p <= 5; ++p)
        fmt::print("{:.{}f}\n", 3.14159, p);
    
    // fmt::join
    fmt::print("\n--- fmt::join ---\n");
    std::vector<int> data = {10, 20, 30, 40, 50};
    fmt::print("Comma: [{}]\n", fmt::join(data, ", "));
    fmt::print("Pipe:  {{ {} }}\n", fmt::join(data, " | "));
    
    // Binary/hex formatting
    fmt::print("\n--- Binary & Hex ---\n");
    for (int i = 0; i < 16; ++i)
        fmt::print("{:2d} = {:04b}  |  {:02X}\n", i, i, i);
    
    // Hex dump
    fmt::print("\n--- Hex Dump ---\n");
    std::string msg = "Hello!";
    fmt::print("Hex of \"{}\": ", msg);
    for (unsigned char c : msg) fmt::print("{:02X} ", c);
    fmt::print("\n");
    
    // Locale formatting
    fmt::print("\n--- Locale Formatting ---\n");
    fmt::print("Default: {}\n", 1000000);
    fmt::print("Locale:  {:L}\n", 1000000);
    
    // Conditional formatting
    fmt::print("\n--- Conditional Formatting ---\n");
    for (int score : {95, 87, 76, 62, 45}) {
        if (score >= 90)      fmt::print(fg(fmt::color::green), "  {}: A\n", score);
        else if (score >= 80) fmt::print(fg(fmt::color::cyan), "  {}: B\n", score);
        else if (score >= 70) fmt::print(fg(fmt::color::yellow), "  {}: C\n", score);
        else                  fmt::print(fg(fmt::color::red), "  {}: F\n", score);
    }
    
    // Table with borders
    fmt::print("\n--- Table with Borders ---\n");
    std::vector<std::tuple<std::string, int, double>> items = {
        {"Apple", 10, 0.99}, {"Banana", 5, 0.59},
        {"Cherry", 20, 2.99}, {"Date", 15, 3.49}
    };
    
    fmt::print("┌{:-<40}┐\n", "");
    fmt::print("│ {:<15} │ {:>5} │ {:>8} │\n", "Item", "Qty", "Price");
    fmt::print("├{:-<40}┤\n", "");
    for (const auto& [name, qty, price] : items)
        fmt::print("│ {:<15} │ {:>5} │ {:>8.2f} │\n", name, qty, price);
    fmt::print("└{:-<40}┘\n", "");
    
    // Memory size formatter
    fmt::print("\n--- Memory Size Formatting ---\n");
    auto format_bytes = [](size_t bytes) {
        const char* units[] = {"B", "KB", "MB", "GB", "TB"};
        int unit = 0;
        double size = bytes;
        while (size >= 1024 && unit < 4) { size /= 1024; ++unit; }
        return fmt::format("{:.2f} {}", size, units[unit]);
    };
    fmt::print("1024 B       = {}\n", format_bytes(1024));
    fmt::print("1048576 B    = {}\n", format_bytes(1048576));
    fmt::print("1073741824 B = {}\n", format_bytes(1073741824));
}

// ============================================================================
// MODULE 4: CHRONO FORMATTING
// ============================================================================
void demo_chrono_formatting() {
    fmt::print(fg(fmt::color::yellow), 
               "\n┌─────────────────────────────────────────────────────────────┐\n");
    fmt::print(fg(fmt::color::yellow), 
               "│ CHRONO FORMATTING: durations, time points, dates           │\n");
    fmt::print(fg(fmt::color::yellow), 
               "└─────────────────────────────────────────────────────────────┘\n\n");
    
    using namespace std::chrono;
    using namespace std::chrono_literals;
    
    // Duration formatting
    fmt::print("--- Duration Formatting ---\n");
    fmt::print("Hours:   {}\n", 2h);
    fmt::print("Minutes: {}\n", 30min);
    fmt::print("Seconds: {}\n", 45s);
    fmt::print("Millis:  {}\n", 500ms);
    fmt::print("Micros:  {}\n", 100us);
    fmt::print("Nanos:   {}\n", 50ns);
    
    // Duration arithmetic
    fmt::print("\n--- Duration Arithmetic ---\n");
    auto total = 2h + 30min + 45s + 500ms;
    fmt::print("Total:      {}\n", total);
    fmt::print("In seconds: {}\n", duration_cast<seconds>(total));
    fmt::print("In minutes: {}\n", duration_cast<minutes>(total));
    
    // Time points
    fmt::print("\n--- Time Points ---\n");
    auto now = system_clock::now();
    fmt::print("Current time: {}\n", now);
    fmt::print("Since epoch:  {}\n", now.time_since_epoch());
    
    // Date/time components
    std::time_t t = std::time(nullptr);
    std::tm* local = std::localtime(&t);
    
    fmt::print("\n--- Date/Time Components ---\n");
    fmt::print("Year:  {}\n", local->tm_year + 1900);
    fmt::print("Month: {:02d}\n", local->tm_mon + 1);
    fmt::print("Day:   {:02d}\n", local->tm_mday);
    fmt::print("Time:  {:02d}:{:02d}:{:02d}\n", 
               local->tm_hour, local->tm_min, local->tm_sec);
    fmt::print("Date:  {:04d}-{:02d}-{:02d}\n",
               local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);
    
    // Performance timing
    fmt::print("\n--- Performance Timing ---\n");
    auto start = high_resolution_clock::now();
    volatile long sum = 0;
    for (long i = 0; i < 5000000; ++i) sum += i;
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(end - start);
    fmt::print("Operation took: {}\n", elapsed);
    fmt::print("Result: {}\n", sum);
    
    // Work day calculation
    fmt::print("\n--- Work Day Calculation ---\n");
    auto work_day = 8h;
    auto lunch = 1h;
    auto breaks = 2 * 15min;
    fmt::print("Work day:      {}\n", work_day);
    fmt::print("Lunch:         {}\n", lunch);
    fmt::print("Breaks:        {}\n", breaks);
    fmt::print("Actual work:   {}\n", work_day - lunch - breaks);
    
    // Countdown
    fmt::print("\n--- Countdown ---\n");
    for (int i = 5; i > 0; --i) {
        fmt::print("\r  {}...", i);
        std::fflush(stdout);
        std::this_thread::sleep_for(200ms);
    }
    fmt::print(fg(fmt::color::green), "\r  Go!          \n");
    
    // Progress bar
    fmt::print("\n--- Progress Bar ---\n");
    const int steps = 30;
    for (int i = 0; i <= steps; ++i) {
        float progress = static_cast<float>(i) / steps;
        int width = 30;
        int filled = static_cast<int>(width * progress);
        fmt::print("\r[");
        fmt::print(fg(fmt::color::green), "{:*>{}}", "", filled);
        fmt::print("{: >{}}", "", width - filled);
        fmt::print("] {:.0f}%", progress * 100);
        std::fflush(stdout);
        std::this_thread::sleep_for(50ms);
    }
    fmt::print("\n");
}

// ============================================================================
// MODULE 5: CUSTOM TYPES
// ============================================================================
void demo_custom_types() {
    fmt::print(fg(fmt::color::yellow), 
               "\n┌─────────────────────────────────────────────────────────────┐\n");
    fmt::print(fg(fmt::color::yellow), 
               "│ CUSTOM TYPES: formatter specialization, enums, complex      │\n");
    fmt::print(fg(fmt::color::yellow), 
               "└─────────────────────────────────────────────────────────────┘\n\n");
    
    // Point2D
    fmt::print("--- Point2D Formatting ---\n");
    Point2D p1{3.14159, 2.71828};
    Point2D p2{0.0, 0.0};
    fmt::print("Point 1: {}\n", p1);
    fmt::print("Point 2: {}\n", p2);
    fmt::print("|p1| = {:.3f}\n", p1.magnitude());
    
    // RGB
    fmt::print("\n--- RGB Formatting ---\n");
    RGB red{255, 0, 0}, green{0, 255, 0}, blue{0, 0, 255};
    fmt::print("Normal:  {}\n", red);
    fmt::print("Colored: {:c}\n", red);
    fmt::print("Colored: {:c}\n", green);
    fmt::print("Colored: {:c}\n", blue);
    
    // Person
    fmt::print("\n--- Person Formatting ---\n");
    Person alice("Alice", 30), bob("Bob", 25);
    fmt::print("{}\n", alice);
    fmt::print("{}\n", bob);
    
    // LogLevel
    fmt::print("\n--- LogLevel Formatting ---\n");
    fmt::print("{}: Application started\n", LogLevel::INFO);
    fmt::print("{}: Processing request...\n", LogLevel::DEBUG);
    fmt::print("{}: Low memory detected\n", LogLevel::WARNING);
    fmt::print("{}: Connection failed\n", LogLevel::ERROR);
    fmt::print("{}: System crash imminent!\n", LogLevel::CRITICAL);
    
    // Complex numbers
    fmt::print("\n--- Complex Numbers ---\n");
    std::complex<double> c1(3.0, 4.0), c2(1.0, -2.0);
    auto c_sum = c1 + c2;
    fmt::print("c1 = {} + {}i\n", c1.real(), c1.imag());
    fmt::print("c2 = {} + {}i\n", c2.real(), c2.imag());
    fmt::print("Sum = {} + {}i\n", c_sum.real(), c_sum.imag());
    fmt::print("|c1| = {:.2f}\n", std::abs(c1));
    
    // Matrix
    fmt::print("\n--- Matrix Formatting ---\n");
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (const auto& row : matrix) {
        fmt::print("  ");
        for (int val : row) fmt::print("{:3}", val);
        fmt::print("\n");
    }
    
    // Stateful formatting
    fmt::print("\n--- Stateful Formatting ---\n");
    struct Counter { int value; };
    Counter counter{42};
    auto fmt_counter = [](const Counter& c) {
        if (c.value > 100) return fmt::format(fg(fmt::color::red), "HIGH: {}", c.value);
        if (c.value > 50)  return fmt::format(fg(fmt::color::yellow), "MED: {}", c.value);
        return fmt::format(fg(fmt::color::green), "LOW: {}", c.value);
    };
    fmt::print("Counter: {}\n", fmt_counter(counter));
}

// ============================================================================
// MODULE 6: PERFORMANCE TIPS
// ============================================================================
void demo_performance_tips() {
    fmt::print(fg(fmt::color::yellow), 
               "\n┌─────────────────────────────────────────────────────────────┐\n");
    fmt::print(fg(fmt::color::yellow), 
               "│ PERFORMANCE TIPS: format_to, buffers, benchmarks            │\n");
    fmt::print(fg(fmt::color::yellow), 
               "└─────────────────────────────────────────────────────────────┘\n\n");
    
    const int N = 100000;
    
    // format() vs format_to()
    fmt::print("--- format() vs format_to() ---\n");
    {
        Timer t("fmt::format (alloc)");
        for (int i = 0; i < N; ++i) {
            auto s = fmt::format("Number: {}", i);
            (void)s;
        }
    }
    {
        Timer t("fmt::format_to (stack)");
        char buf[256];
        for (int i = 0; i < N; ++i) {
            auto end = fmt::format_to(buf, "Number: {}", i);
            *end = '\0';
        }
    }
    
    // Buffer reuse
    fmt::print("\n--- Buffer Reuse ---\n");
    {
        Timer t("With buffer reuse");
        std::string reusable;
        reusable.reserve(1024);
        for (int i = 0; i < N; ++i) {
            reusable.clear();
            fmt::format_to(std::back_inserter(reusable), "Number: {}", i);
        }
    }
    
    // vs other methods
    fmt::print("\n--- vs Other Methods ---\n");
    int value = 42;
    {
        Timer t("fmt::format");
        for (int i = 0; i < N; ++i) {
            auto s = fmt::format("Value: {}", value);
            (void)s;
        }
    }
    {
        Timer t("stringstream");
        for (int i = 0; i < N; ++i) {
            std::ostringstream oss;
            oss << "Value: " << value;
            auto s = oss.str();
            (void)s;
        }
    }
    {
        Timer t("to_string + concat");
        for (int i = 0; i < N; ++i) {
            auto s = "Value: " + std::to_string(value);
            (void)s;
        }
    }
    
    // Conditional formatting
    fmt::print("\n--- Conditional Formatting ---\n");
    bool verbose = false;
    {
        Timer t("Always format");
        for (int i = 0; i < N; ++i) {
            auto s = fmt::format("Debug: {}", i);
            if (verbose) fmt::print("{}\n", s);
        }
    }
    {
        Timer t("Conditional format");
        for (int i = 0; i < N; ++i) {
            if (verbose) fmt::print("Debug: {}\n", i);
        }
    }
    
    // Memory buffer
    fmt::print("\n--- Memory Buffer ---\n");
    {
        Timer t("Memory buffer");
        fmt::memory_buffer buf;
        for (int i = 0; i < N; ++i) {
            buf.clear();
            fmt::format_to(std::back_inserter(buf), "Number: {}", i);
        }
    }
    
    // Best practices
    fmt::print("\n--- Best Practices ---\n");
    fmt::print(fg(fmt::color::green), "✓ DO:\n");
    fmt::print("  • Use format_to() with pre-allocated buffers\n");
    fmt::print("  • Reuse format buffers when possible\n");
    fmt::print("  • Use fmt::join() for containers\n");
    fmt::print("  • Batch format operations\n\n");
    
    fmt::print(fg(fmt::color::red), "✗ DON'T:\n");
    fmt::print("  • Don't create strings when not needed\n");
    fmt::print("  • Don't format debug messages if not required\n");
    fmt::print("  • Don't use stringstream (slower)\n");
    fmt::print("  • Don't concatenate with + for complex strings\n");
    
    // Stack vs heap
    fmt::print("\n--- Stack vs Heap ---\n");
    {
        Timer t("Heap (format)");
        for (int i = 0; i < N; ++i) {
            auto s = fmt::format("Hello World {}", i);
            (void)s.size();
        }
    }
    {
        Timer t("Stack (format_to)");
        char buf[64];
        for (int i = 0; i < N; ++i) {
            auto end = fmt::format_to(buf, "Hello World {}", i);
            (void)(end - buf);
        }
    }
    fmt::print("\n💡 format_to with stack buffer avoids heap allocations\n");
}
