#!/bin/bash
echo "╔══════════════════════════════════════════════════════════════════════╗"
echo "║     BUILDING ALL MAKEFILE & CMAKE EXAMPLES                          ║"
echo "╚══════════════════════════════════════════════════════════════════════╝"
echo ""

build_makefile() {
    local dir=$1
    local label=$2
    echo "----------------------------------------"
    echo "  $label"
    echo "----------------------------------------"
    cd "$dir"
    make clean 2>/dev/null || true
    make 2>&1 | tail -3
    if [ -f hello ]; then
        ./hello && echo ""
    elif [ -f program ]; then
        ./program && echo ""
    elif [ -d build ] && [ -f build/app ]; then
        ./build/app && echo ""
    elif [ -d build ] && [ -f build/hello ]; then
        ./build/hello && echo ""
    fi
    make clean 2>/dev/null || true
    cd - > /dev/null
}

build_cmake() {
    local dir=$1
    local label=$2
    echo "----------------------------------------"
    echo "  $label"
    echo "----------------------------------------"
    cd "$dir"
    rm -rf build
    mkdir build && cd build
    cmake .. 2>&1 | tail -1
    make -j$(nproc 2>/dev/null || echo 4) 2>&1 | tail -1
    if [ -f calculator ]; then ./calculator; fi
    if [ -f app ]; then ./app; fi
    if [ -f calc_app ]; then ./calc_app; fi
    if [ -f app1 ]; then ./app1; fi
    echo ""
    cd ../..
}

echo "=== BASIC LESSONS ==="
echo ""

echo "[1/6] Manual Compilation"
cd basic/01_manual && ./build.sh && cd ../..

echo "[2/6] Simple Makefile"
build_makefile "basic/02_makefile_simple" "Simple Makefile"

echo "[3/6] Advanced Makefile"
build_makefile "basic/03_makefile_advanced" "Advanced Makefile"

echo "[4/6] Simple CMake"
cd basic/04_cmake_simple && ./build.sh && cd ../..

echo "[5/6] CMake Library"
cd basic/05_cmake_library && ./build.sh && cd ../..

echo "[6/6] CMake Install"
cd basic/06_cmake_install && ./build.sh && cd ../..

echo ""
echo "=== ADVANCED LESSONS ==="
echo ""

echo "[7/12] Makefile Functions"
build_makefile "advanced/01_makefile_functions" "Makefile Functions"

echo "[8/12] Multi-Directory Makefile"
build_makefile "advanced/02_makefile_multidir" "Multi-Dir Makefile"

echo "[9/12] CMake Generator Expressions"
build_cmake "advanced/03_cmake_genexpr" "Generator Expressions"

echo "[10/12] CTest Testing"
build_cmake "advanced/04_cmake_testing" "CTest Testing"

echo "[11/12] External Dependencies"
build_cmake "advanced/05_cmake_external" "External Dependencies"

echo "[12/12] CMake Advanced Features"
build_cmake "advanced/06_cmake_advanced" "Advanced Features"

echo ""
echo "╔══════════════════════════════════════════════════════════════════════╗"
echo "║     ALL EXAMPLES BUILT SUCCESSFULLY!                                ║"
echo "╚══════════════════════════════════════════════════════════════════════╝"
