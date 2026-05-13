#ifndef STL_CONTAINERS_H
#define STL_CONTAINERS_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

void demonstrate_stl() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ STL CONTAINERS & ALGORITHMS: vector, map, set, algorithms       │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // Vector
    std::cout << "\n--- Vector ---\n";
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Original: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << "\n";
    
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << "\n";
    
    auto it = std::find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        std::cout << "Found 7 at index: " 
                  << std::distance(numbers.begin(), it) << "\n";
    }
    
    numbers.erase(
        std::remove_if(numbers.begin(), numbers.end(), 
                      [](int n) { return n % 2 == 0; }),
        numbers.end()
    );
    std::cout << "After removing even numbers: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << "\n";
    
    // Map with structured bindings
    std::cout << "\n--- Map with Structured Bindings ---\n";
    std::map<std::string, int> ages;
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages["Charlie"] = 35;
    
    for (const auto& [name, age] : ages) {
        std::cout << name << " is " << age << " years old\n";
    }
    
    // Unordered map
    std::cout << "\n--- Unordered Map ---\n";
    std::unordered_map<std::string, double> prices;
    prices["apple"] = 0.99;
    prices["banana"] = 0.59;
    prices["cherry"] = 2.99;
    
    prices.insert_or_assign("apple", 1.49);
    prices.insert_or_assign("date", 3.49);
    
    for (const auto& [fruit, price] : prices) {
        std::cout << fruit << ": $" << price << "\n";
    }
    
    // Set
    std::cout << "\n--- Set ---\n";
    std::set<int> unique_numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    std::cout << "Set elements (sorted, unique): ";
    for (const auto& n : unique_numbers) std::cout << n << " ";
    std::cout << "\n";
    
    // Algorithms
    std::cout << "\n--- Algorithms ---\n";
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::vector<int> squares;
    std::transform(v.begin(), v.end(), std::back_inserter(squares),
                  [](int n) { return n * n; });
    
    std::cout << "Squares: ";
    for (const auto& n : squares) std::cout << n << " ";
    std::cout << "\n";
    
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Sum of 1..10 = " << sum << "\n";
    
    bool all_positive = std::all_of(v.begin(), v.end(), 
                                    [](int n) { return n > 0; });
    bool any_greater_than_5 = std::any_of(v.begin(), v.end(), 
                                          [](int n) { return n > 5; });
    
    std::cout << "All positive? " << (all_positive ? "Yes" : "No") << "\n";
    std::cout << "Any > 5? " << (any_greater_than_5 ? "Yes" : "No") << "\n";
    
    // List
    std::cout << "\n--- List ---\n";
    std::list<std::string> tasks = {"Wake up", "Exercise", "Study C++", "Sleep"};
    
    auto task_it = std::find(tasks.begin(), tasks.end(), "Study C++");
    if (task_it != tasks.end()) {
        tasks.insert(task_it, "Eat breakfast");
    }
    
    std::cout << "Tasks:\n";
    for (const auto& task : tasks) {
        std::cout << "  - " << task << "\n";
    }
}

#endif
