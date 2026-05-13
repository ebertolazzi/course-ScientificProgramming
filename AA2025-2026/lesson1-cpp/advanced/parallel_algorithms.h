#ifndef PARALLEL_ALGORITHMS_H
#define PARALLEL_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <cmath>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::string name;
    
public:
    // FIXED: initialization order
    Timer(const std::string& n) 
        : start(std::chrono::high_resolution_clock::now()), name(n) {}
    
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << name << " took " << duration.count() << " μs\n";
    }
};

std::vector<int> generate_random_vector(size_t size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    for (auto& val : vec) {
        val = dis(gen);
    }
    return vec;
}

void demonstrate_parallel_algorithms() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ PARALLEL ALGORITHMS: execution policies & parallel STL         │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    const size_t data_size = 5000000;
    std::vector<int> data = generate_random_vector(data_size);
    
    // Standard sort (sequential)
    std::cout << "\n--- Standard Sort (Sequential) ---\n";
    {
        auto vec_copy = data;
        Timer t("Sequential sort");
        std::sort(vec_copy.begin(), vec_copy.end());
    }
    
    // Standard transform
    std::cout << "\n--- Standard Transform ---\n";
    std::vector<double> results(data.size());
    
    {
        Timer t("Standard transform");
        std::transform(data.begin(), data.end(), 
                      results.begin(), [](int x) { 
                          return std::sqrt(static_cast<double>(x)); 
                      });
    }
    
    // Reduce (sequential)
    std::cout << "\n--- Standard Reduce ---\n";
    {
        Timer t("Standard accumulate");
        long long sum = std::accumulate(data.begin(), data.end(), 0LL);
        std::cout << "  Sum: " << sum << "\n";
    }
    
    // Scan operations (C++17)
    std::cout << "\n--- Scan Operations (C++17) ---\n";
    std::vector<int> small_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> inclusive_result(small_data.size());
    std::vector<int> exclusive_result(small_data.size());
    
    std::inclusive_scan(small_data.begin(), small_data.end(), 
                       inclusive_result.begin());
    
    std::exclusive_scan(small_data.begin(), small_data.end(), 
                       exclusive_result.begin(), 0);
    
    std::cout << "Original:        ";
    for (auto x : small_data) std::cout << x << " ";
    std::cout << "\nInclusive scan:  ";
    for (auto x : inclusive_result) std::cout << x << " ";
    std::cout << "\nExclusive scan:  ";
    for (auto x : exclusive_result) std::cout << x << " ";
    std::cout << "\n";
    
    // Note about parallel execution policies
    std::cout << "\n--- Note on Parallel Execution ---\n";
    std::cout << "C++17 introduces execution policies:\n";
    std::cout << "  std::execution::seq       - sequential execution\n";
    std::cout << "  std::execution::par       - parallel execution\n";
    std::cout << "  std::execution::par_unseq - parallel + vectorized\n";
    std::cout << "These require TBB (Intel Threading Building Blocks) or\n";
    std::cout << "a compiler with full C++17 parallel STL support.\n";
    std::cout << "Example: std::sort(std::execution::par, vec.begin(), vec.end());\n";
}

#endif
