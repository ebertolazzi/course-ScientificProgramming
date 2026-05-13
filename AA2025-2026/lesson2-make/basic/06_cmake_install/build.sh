#!/bin/bash
echo "=== CMake Install Example ==="
mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install
make -j$(nproc 2>/dev/null || echo 4)
echo ""
echo "Installing to ../install ..."
make install
echo ""
echo "Installed files:"
find ../install -type f 2>/dev/null | sort
echo ""
echo "Running installed app:"
../install/bin/mylib_app
