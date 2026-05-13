#!/bin/bash
echo "=== CMake Simple Build ==="
echo "Step 1: Create build directory (out-of-source build)"
mkdir -p build
cd build
echo "Step 2: Configure (generate build files)"
cmake ..
echo ""
echo "Step 3: Build"
make -j$(nproc 2>/dev/null || echo 4)
echo ""
echo "Step 4: Run"
./calculator
