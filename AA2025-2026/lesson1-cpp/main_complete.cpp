/*
 * C++17 COMPLETE LESSON - MAIN
 * ============================
 * This is the main entry point for the complete C++17 lesson.
 * It demonstrates both basic and advanced C++17 features.
 * 
 * Compile: g++ -std=c++17 -pthread -O2 main_complete.cpp -o lesson
 * Run: ./lesson
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// Basic modules
#include "basic/basic_syntax.h"
#include "basic/functions_templates.h"
#include "basic/memory_management.h"
#include "basic/oop_basics.h"
#include "basic/stl_containers.h"
#include "basic/modern_cpp17.h"

// Advanced modules
#include "advanced/filesystem_ops.h"
#include "advanced/parallel_algorithms.h"
#include "advanced/advanced_templates.h"
#include "advanced/concurrency.h"
#include "advanced/string_processing.h"
#include "advanced/attributes_and_literals.h"
#include "advanced/advanced_techniques.h"

void print_section(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(70, '=') << "\n";
}

int main() {
    std::cout << "╔══════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║              C++17 COMPLETE LESSON - ALL FEATURES               ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    // ==========================================
    // PART 1: BASIC C++17 FEATURES
    // ==========================================
    print_section("PART 1: BASIC C++17 FEATURES");
    
    std::cout << "\n▶ Module 1: Basic Syntax";
    demonstrate_basic_syntax();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 2: Functions and Templates";
    demonstrate_functions();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 3: Memory Management";
    demonstrate_memory_management();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 4: Object-Oriented Programming";
    demonstrate_oop();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 5: STL Containers and Algorithms";
    demonstrate_stl();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 6: Modern C++17 Features";
    demonstrate_modern_cpp17();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    // ==========================================
    // PART 2: ADVANCED C++17 FEATURES
    // ==========================================
    print_section("PART 2: ADVANCED C++17 FEATURES");
    
    std::cout << "\n▶ Module 7: Filesystem Operations";
    demonstrate_filesystem();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 8: Parallel Algorithms";
    demonstrate_parallel_algorithms();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 9: Advanced Templates";
    demonstrate_advanced_templates();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 10: Concurrency";
    demonstrate_concurrency();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 11: String Processing";
    demonstrate_string_processing();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 12: Attributes and Literals";
    demonstrate_attributes_and_literals();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    std::cout << "\n▶ Module 13: Advanced Techniques";
    demonstrate_advanced_techniques();
    
    // ==========================================
    // SUMMARY
    // ==========================================
    print_section("LESSON SUMMARY");
    
    std::cout << "\n📚 Topics Covered:\n\n";
    
    std::cout << "BASIC C++17 FEATURES:\n";
    std::cout << "  ✓ Auto type deduction and structured bindings\n";
    std::cout << "  ✓ Lambda expressions and constexpr functions\n";
    std::cout << "  ✓ Smart pointers (unique_ptr, shared_ptr, weak_ptr)\n";
    std::cout << "  ✓ RAII and move semantics\n";
    std::cout << "  ✓ OOP: inheritance, polymorphism, abstract classes\n";
    std::cout << "  ✓ STL containers and algorithms\n";
    std::cout << "  ✓ std::optional, std::variant, std::any\n";
    std::cout << "  ✓ if constexpr, fold expressions\n";
    
    std::cout << "\nADVANCED C++17 FEATURES:\n";
    std::cout << "  ✓ std::filesystem operations\n";
    std::cout << "  ✓ Parallel algorithms with execution policies\n";
    std::cout << "  ✓ Advanced templates (SFINAE, enable_if, detection idiom)\n";
    std::cout << "  ✓ Concurrency (threads, mutexes, shared_mutex, scoped_lock)\n";
    std::cout << "  ✓ Boyer-Moore search, to_chars/from_chars\n";
    std::cout << "  ✓ Attributes ([[nodiscard]], [[fallthrough]], [[maybe_unused]])\n";
    std::cout << "  ✓ std::byte, copy elision, constexpr lambda, std::launder\n";
    
    std::cout << "\n✅ Total: 13 comprehensive modules covering all C++17 features\n";
    std::cout << "\n🎯 Compile with: g++ -std=c++17 -pthread -O2 main_complete.cpp -o lesson\n";
    std::cout << "🚀 Run with: ./lesson\n\n";
    
    std::cout << "╔══════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    END OF C++17 LESSON                         ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    return 0;
}
