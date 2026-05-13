#!/bin/bash
set -e
echo "Building Eigen + {fmt} Lesson..."
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
echo ""
echo "Build complete!"
echo "  ./build/eigen_demo         - Full lesson"
echo "  ./build/eigen_demo_single  - Quick demo"
