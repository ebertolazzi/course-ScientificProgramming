#!/bin/bash
echo "Compiling C++17 Complete Lesson..."
g++ -std=c++17 -pthread -O2 -Wall -Wextra main_complete.cpp -o lesson
if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "Run with: ./lesson"
else
    echo "❌ Compilation failed"
    exit 1
fi
