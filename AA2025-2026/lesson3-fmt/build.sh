#!/bin/bash
set -e

echo "Building {fmt} Lesson..."
echo "========================"

# Check for fmt.pc
if pkg-config --exists fmt 2>/dev/null; then
    FMT_CFLAGS=$(pkg-config --cflags fmt)
    FMT_LIBS=$(pkg-config --libs fmt)
    echo "Using pkg-config: $FMT_CFLAGS $FMT_LIBS"
else
    FMT_CFLAGS=""
    FMT_LIBS="-lfmt"
    echo "Using default flags"
fi

# CMake build
if command -v cmake &> /dev/null; then
    echo "Using CMake..."
    mkdir -p build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    cp fmt_demo ..
    cd ..
else
    echo "Direct compilation..."
    g++ -std=c++17 -O2 -Wall -Wextra \
        -I./include \
        $FMT_CFLAGS \
        src/main.cpp \
        $FMT_LIBS \
        -o fmt_demo
fi

echo ""
echo "✅ Build complete! Run: ./fmt_demo"
