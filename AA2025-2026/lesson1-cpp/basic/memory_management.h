#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

class FileHandler {
private:
    std::string filename;
    bool is_open;
    
public:
    explicit FileHandler(const std::string& fname) 
        : filename(fname), is_open(true) {
        std::cout << "File " << filename << " opened\n";
    }
    
    ~FileHandler() {
        if (is_open) {
            std::cout << "File " << filename << " closed (RAII)\n";
        }
    }
    
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;
    
    FileHandler(FileHandler&& other) noexcept 
        : filename(std::move(other.filename)), is_open(other.is_open) {
        other.is_open = false;
        std::cout << "FileHandler moved\n";
    }
};

class Resource {
private:
    size_t size;
    int* data;
    
public:
    // FIXED: initialization order (size before data)
    explicit Resource(size_t s) : size(s), data(new int[s]) {
        std::cout << "Resource allocated (size " << size << ")\n";
        std::fill(data, data + size, 0);
    }
    
    ~Resource() {
        delete[] data;
        std::cout << "Resource freed (size " << size << ")\n";
    }
    
    Resource(Resource&& other) noexcept 
        : size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Resource moved\n";
    }
    
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        std::cout << "Resource move-assigned\n";
        return *this;
    }
    
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
};

void demonstrate_memory_management() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ MEMORY MANAGEMENT: smart pointers, RAII, move semantics        │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // Raw pointers
    int value = 42;
    int* raw_ptr = &value;
    std::cout << "Raw pointer value: " << *raw_ptr << "\n";
    
    // References
    int& reference = value;
    reference = 100;
    std::cout << "After reference modification: " << value << "\n";
    
    // unique_ptr
    {
        std::unique_ptr<int> unique_int = std::make_unique<int>(200);
        std::cout << "unique_ptr value: " << *unique_int << "\n";
        
        auto moved_ptr = std::move(unique_int);
        std::cout << "Moved unique_ptr: " << *moved_ptr << "\n";
    }
    
    // shared_ptr
    {
        std::shared_ptr<double> shared1 = std::make_shared<double>(3.14);
        {
            std::shared_ptr<double> shared2 = shared1;
            std::cout << "shared_ptr value: " << *shared1 
                      << ", use count: " << shared1.use_count() << "\n";
        }
        std::cout << "After inner scope, use count: " 
                  << shared1.use_count() << "\n";
    }
    
    // weak_ptr
    std::weak_ptr<double> weak;
    {
        auto shared = std::make_shared<double>(2.718);
        weak = shared;
        if (auto locked = weak.lock()) {
            std::cout << "weak_ptr locked value: " << *locked << "\n";
        }
    }
    if (weak.expired()) {
        std::cout << "weak_ptr expired (object destroyed)\n";
    }
    
    // RAII demonstration
    {
        FileHandler file("example.txt");
    }
    
    // Move semantics
    Resource res1(100);
    Resource res2 = std::move(res1);
    Resource res3(50);
    res3 = std::move(res2);
    
    // std::move with containers
    std::vector<int> original{1, 2, 3, 4, 5};
    std::vector<int> moved_to = std::move(original);
    std::cout << "After move, original size: " << original.size() 
              << ", moved_to size: " << moved_to.size() << "\n";
}

#endif
