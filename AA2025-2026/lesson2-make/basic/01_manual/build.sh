#!/bin/bash
echo "=== Lesson 1: Manual Compilation ==="
echo ""
echo "Step 1: Compile source files to object files..."
g++ -std=c++17 -c src/hello.cpp -o hello.o
g++ -std=c++17 -c src/mymath.cpp -o mymath.o
echo "Step 2: Link object files into executable..."
g++ hello.o mymath.o -o hello
echo "Step 3: Run..."
./hello
echo ""
echo "Problem: Every file compiled every time. No dependency tracking."
rm -f hello.o mymath.o hello
