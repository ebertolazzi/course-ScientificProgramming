#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <future>
#include <vector>
#include <chrono>

class ThreadSafeCounter {
private:
    mutable std::shared_mutex mutex;
    int value = 0;
    
public:
    int get() const {
        std::shared_lock lock(mutex);
        return value;
    }
    
    void increment() {
        std::unique_lock lock(mutex);
        ++value;
    }
};

class BankAccount {
private:
    std::string name;
    double balance;
    std::mutex mutex;  // FIXED: mutex last in initialization
    
public:
    // FIXED: correct initialization order (name, balance, mutex)
    BankAccount(const std::string& n, double initial) 
        : name(n), balance(initial) {}
    
    static void transfer(BankAccount& from, BankAccount& to, double amount) {
        std::scoped_lock lock(from.mutex, to.mutex);
        
        if (from.balance >= amount) {
            from.balance -= amount;
            to.balance += amount;
            std::cout << "Transfer: " << amount 
                      << " from " << from.name 
                      << " to " << to.name << "\n";
        }
    }
    
    double get_balance() const { return balance; }
    std::string get_name() const { return name; }
};

void demonstrate_concurrency() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ CONCURRENCY: threads, shared_mutex, scoped_lock, async        │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // Basic threading with shared_mutex
    std::cout << "\n--- Thread-Safe Counter with shared_mutex ---\n";
    ThreadSafeCounter counter;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 1000; ++j) {
                counter.increment();
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "Final counter value: " << counter.get() << "\n";
    
    // Scoped lock for deadlock avoidance
    std::cout << "\n--- Scoped Lock (Deadlock Avoidance) ---\n";
    BankAccount account1("Alice", 1000);
    BankAccount account2("Bob", 500);
    
    std::cout << "Before: " << account1.get_name() << "=" 
              << account1.get_balance() << ", "
              << account2.get_name() << "=" 
              << account2.get_balance() << "\n";
    
    std::thread t1([&]() {
        for (int i = 0; i < 10; ++i) {
            BankAccount::transfer(account1, account2, 10);
        }
    });
    
    std::thread t2([&]() {
        for (int i = 0; i < 10; ++i) {
            BankAccount::transfer(account2, account1, 5);
        }
    });
    
    t1.join();
    t2.join();
    
    std::cout << "After:  " << account1.get_name() << "=" 
              << account1.get_balance() << ", "
              << account2.get_name() << "=" 
              << account2.get_balance() << "\n";
    
    // Future and async
    std::cout << "\n--- Future and Async ---\n";
    auto future1 = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    });
    
    std::cout << "Future result: " << future1.get() << "\n";
    
    // Atomic operations
    std::cout << "\n--- Atomic Operations ---\n";
    std::atomic<int> atomic_counter{0};
    std::vector<std::thread> atomic_threads;
    
    for (int i = 0; i < 10; ++i) {
        atomic_threads.emplace_back([&atomic_counter]() {
            for (int j = 0; j < 1000; ++j) {
                atomic_counter.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    
    for (auto& t : atomic_threads) t.join();
    std::cout << "Atomic counter: " << atomic_counter << "\n";
    
    // Hardware concurrency
    std::cout << "\n--- Hardware Info ---\n";
    unsigned int concurrency = std::thread::hardware_concurrency();
    std::cout << "Hardware concurrency: " << concurrency << " threads\n";
}

#endif
