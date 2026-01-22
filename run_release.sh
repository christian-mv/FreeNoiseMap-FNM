#!/bin/bash
set -e

# Setup Paths for Qt Tools (CMake, Ninja) and Qt Libraries
export PATH=$PATH:/home/christian/Qt/Tools/CMake/bin:/home/christian/Qt/Tools/Ninja
QT_PREFIX_PATH="/home/christian/Qt/6.9.1/gcc_64"

BUILD_DIR="build_release"
SOURCE_DIR="code"
EXECUTABLE="$BUILD_DIR/ui/FreeNoiseMap"

echo "=== Configuring (Release) ==="
cmake -S "$SOURCE_DIR" -B "$BUILD_DIR" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH="$QT_PREFIX_PATH" \
      -GNinja

echo "=== Building (Release) ==="
cmake --build "$BUILD_DIR" --parallel

if [ -f "$EXECUTABLE" ]; then
    echo "=== Running ==="
    "$EXECUTABLE"
else
    echo "Error: Executable not found at $EXECUTABLE"
    exit 1
fi
