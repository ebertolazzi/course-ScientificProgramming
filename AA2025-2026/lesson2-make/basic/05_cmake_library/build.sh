#!/bin/bash
echo "=== CMake Library Build ==="
mkdir -p build && cd build
cmake ..
make -j$(nproc 2>/dev/null || echo 4)
echo ""
echo "Running app..."
./app
echo ""
echo "Static library created:"
ls -la libstringutils.a 2>/dev/null || echo "(linked internally)"
