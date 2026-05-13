#ifndef FMT_LESSON_H
#define FMT_LESSON_H

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>
#include <fmt/os.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <chrono>
#include <thread>
#include <complex>
#include <cmath>
#include <cstdint>

void demo_basic_formatting();
void demo_colors_styles();
void demo_advanced_formatting();
void demo_chrono_formatting();
void demo_custom_types();
void demo_performance_tips();

inline void print_section(const std::string& title) {
    fmt::print("\n{}\n", std::string(70, '='));
    fmt::print("  {}\n", title);
    fmt::print("{}\n", std::string(70, '='));
}

#endif
