#ifndef FILESYSTEM_OPS_H
#define FILESYSTEM_OPS_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void demonstrate_filesystem() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ FILESYSTEM: path manipulation, directory ops, file iteration   │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    // Path operations
    std::cout << "\n--- Path Operations ---\n";
    fs::path current = fs::current_path();
    std::cout << "Current path: " << current << "\n";
    
    fs::path example_path = "/home/user/documents/file.txt";
    std::cout << "Path: " << example_path << "\n";
    std::cout << "  Filename: " << example_path.filename() << "\n";
    std::cout << "  Stem: " << example_path.stem() << "\n";
    std::cout << "  Extension: " << example_path.extension() << "\n";
    std::cout << "  Parent path: " << example_path.parent_path() << "\n";
    
    // Path concatenation
    fs::path combined = fs::path("folder") / "subfolder" / "file.txt";
    std::cout << "Combined path: " << combined << "\n";
    
    // Create and manipulate directories
    std::cout << "\n--- Directory Operations ---\n";
    fs::path test_dir = current / "test_cpp17_demo";
    
    if (!fs::exists(test_dir)) {
        fs::create_directory(test_dir);
        std::cout << "Created directory: " << test_dir << "\n";
    }
    
    // Create file for demonstration
    fs::path test_file = test_dir / "demo.txt";
    {
        std::ofstream file(test_file);
        file << "Hello C++17 Filesystem!\n";
        file << "This demonstrates file operations.\n";
    }
    
    if (fs::exists(test_file)) {
        auto file_size = fs::file_size(test_file);
        std::cout << "File size: " << file_size << " bytes\n";
        
        // Copy and rename
        fs::path copy_file = test_dir / "demo_copy.txt";
        fs::copy_file(test_file, copy_file, fs::copy_options::overwrite_existing);
        std::cout << "Copied to: " << copy_file.filename() << "\n";
        
        fs::path renamed = test_dir / "renamed.txt";
        fs::rename(copy_file, renamed);
        std::cout << "Renamed to: " << renamed.filename() << "\n";
    }
    
    // Directory iteration
    std::cout << "\n--- Directory Contents ---\n";
    for (const auto& entry : fs::directory_iterator(test_dir)) {
        std::cout << "  " << (entry.is_directory() ? "[DIR]  " : "[FILE] ")
                  << entry.path().filename();
        if (entry.is_regular_file()) {
            std::cout << " (" << entry.file_size() << " bytes)";
        }
        std::cout << "\n";
    }
    
    // Space information
    std::cout << "\n--- Space Information ---\n";
    try {
        auto space = fs::space(current);
        std::cout << "Capacity: " << space.capacity / 1024 / 1024 << " MB\n";
        std::cout << "Free:     " << space.free / 1024 / 1024 << " MB\n";
        std::cout << "Available:" << space.available / 1024 / 1024 << " MB\n";
    } catch (const fs::filesystem_error& e) {
        std::cout << "Space info not available: " << e.what() << "\n";
    }
    
    // Cleanup
    std::cout << "\n--- Cleanup ---\n";
    if (fs::exists(test_dir)) {
        fs::remove_all(test_dir);
        std::cout << "Removed test directory\n";
    }
}

#endif
