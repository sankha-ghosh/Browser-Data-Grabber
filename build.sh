#!/bin/bash

# Build script for Stealer Builder (Linux)

set -e

echo "==================================="
echo "Stealer Builder - Build Script"
echo "==================================="
echo ""

# Check for required tools
echo "[1/5] Checking dependencies..."

if ! command -v cmake &> /dev/null; then
    echo "ERROR: cmake not found. Please install cmake."
    exit 1
fi

if ! command -v g++ &> /dev/null; then
    echo "ERROR: g++ not found. Please install build-essential."
    exit 1
fi

# Check for Qt6
if ! command -v qmake6 &> /dev/null && ! command -v qmake &> /dev/null; then
    echo "WARNING: Qt6 might not be installed. Continuing anyway..."
fi

echo "✓ Basic dependencies found"
echo ""

# (Fonts are included in the repo and embedded via resources.qrc)

# Check for MinGW-w64 (required for cross-compilation)
echo "[2/5] Checking for MinGW-w64 cross-compiler..."

if command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    echo "✓ MinGW-w64 found: $(x86_64-w64-mingw32-g++ --version | head -n1)"
else
    echo "⚠ WARNING: MinGW-w64 not found!"
    echo ""
    echo "The GUI will build, but you won't be able to compile Windows executables."
    echo ""
    echo "To install MinGW-w64:"
    echo "  Ubuntu/Debian: sudo apt-get install mingw-w64"
    echo "  Fedora/RHEL:   sudo dnf install mingw64-gcc mingw64-gcc-c++"
    echo "  Arch:          sudo pacman -S mingw-w64-gcc"
    echo ""
    read -p "Continue anyway? (y/n) " -n 1 -r
    echo ""
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

echo ""

# Create build directory
echo "[3/5] Creating build directory..."
mkdir -p build
cd build

# Run CMake
echo "[4/5] Running CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
echo "[5/5] Building..."
make -j$(nproc)

echo ""
echo "==================================="
echo "✓ Build successful!"
echo "==================================="
echo ""
echo "Run the application with:"
echo "  ./bin/StealerBuilder"
echo ""




