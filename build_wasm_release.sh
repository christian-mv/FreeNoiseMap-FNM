#!/bin/bash
set -e

# ==============================================================================
# Build Script for WebAssembly (Release)
# ==============================================================================
# Prerequisites:
# 1. Emscripten SDK (emsdk) installed and activated.
#    Recommended version for Qt 6.9: 3.1.70
# 2. Qt 6.9 WebAssembly version installed.
#
# Usage:
#   ./build_wasm_release.sh
#
# Configuration (Environment Variables):
#   QT_DIR          Path to Qt WebAssembly installation (default: ~/Qt/6.9.1/wasm_singlethread)
#   EMSCRIPTEN_ROOT Path to emsdk directory (default: ~/emsdk)
# ==============================================================================

# --- Configuration ---
# Default paths - Adjust these if your installation differs
DEFAULT_QT_DIR="$HOME/Qt/6.9.1/wasm_multithread"
DEFAULT_EMSCRIPTEN_ROOT="$HOME/emsdk"

QT_DIR="${QT_DIR:-$DEFAULT_QT_DIR}"
EMSCRIPTEN_ROOT="${EMSCRIPTEN_ROOT:-$DEFAULT_EMSCRIPTEN_ROOT}"

PROJECT_ROOT="$(pwd)"
SOURCE_DIR="$PROJECT_ROOT/code"
BUILD_DIR="$PROJECT_ROOT/build_wasm_release"
CONCURRENCY=$(nproc)

# --- Validation ---

if [ ! -d "$SOURCE_DIR" ]; then
    echo "❌ Error: Source directory '$SOURCE_DIR' not found."
    echo "   Please run this script from the project root."
    exit 1
fi

if [ ! -d "$QT_DIR" ]; then
    echo "❌ Error: Qt directory not found at '$QT_DIR'."
    echo "   Please set the QT_DIR environment variable to your Qt WebAssembly installation."
    echo "   Example: export QT_DIR=~/Qt/6.9.1/wasm_multithread"
    exit 1
fi

QT_CMAKE="$QT_DIR/bin/qt-cmake"
if [ ! -f "$QT_CMAKE" ]; then
    echo "❌ Error: qt-cmake not found at '$QT_CMAKE'."
    echo "   Check your QT_DIR path."
    exit 1
fi

if [ ! -f "$EMSCRIPTEN_ROOT/emsdk_env.sh" ]; then
    echo "❌ Error: Emscripten SDK environment script not found at '$EMSCRIPTEN_ROOT/emsdk_env.sh'."
    echo "   Please set EMSCRIPTEN_ROOT to your emsdk installation."
    exit 1
fi

# --- Setup Environment ---

echo "🔧 Setting up Emscripten environment..."
source "$EMSCRIPTEN_ROOT/emsdk_env.sh"

echo "   Qt Path: $QT_DIR"
echo "   Emscripten Path: $EMSCRIPTEN_ROOT"

# --- Build Process ---

echo "📁 Creating build directory: $BUILD_DIR"
mkdir -p "$BUILD_DIR"

echo "⚙️  Configuring project (Release)..."
# Note: We use qt-cmake which automatically handles the toolchain file

GENERATOR=""
if which ninja >/dev/null 2>&1; then
    GENERATOR="-GNinja"
fi

"$QT_CMAKE" -S "$SOURCE_DIR" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    $GENERATOR

# Check if configuration failed
if [ $? -ne 0 ]; then
    echo "❌ CMake configuration failed."
    exit 1
fi

# Find cmake
CMAKE_EXE=$(which cmake 2>/dev/null || echo "")
if [ -z "$CMAKE_EXE" ]; then
    # Try to find it in Qt Tools directory
    QT_TOOLS_DIR="$(dirname "$(dirname "$(dirname "$(dirname "$QT_DIR")")")")/Tools/CMake/bin"
    if [ -f "$QT_TOOLS_DIR/cmake" ]; then
        CMAKE_EXE="$QT_TOOLS_DIR/cmake"
    else
        # Fallback to a common guess if the above fails
        CMAKE_EXE="$HOME/Qt/Tools/CMake/bin/cmake"
    fi
fi

if [ ! -f "$CMAKE_EXE" ]; then
    echo "❌ Error: cmake not found. Please install cmake or ensure it is in your PATH."
    exit 1
fi

echo "🚀 Building project..."
"$CMAKE_EXE" --build "$BUILD_DIR" --parallel "$CONCURRENCY"

if [ $? -eq 0 ]; then
    echo "✅ Build completed successfully!"
    echo "   Artifacts are located in: $BUILD_DIR"
    
    HTML_FILE="$BUILD_DIR/ui/FreeNoiseMap.html"
    if [ -f "$HTML_FILE" ]; then
        echo "🔧 Patching HTML splash screen..."
        
        # Ensure icon is in the same directory as HTML
        cp "$SOURCE_DIR/ui/icons/app_icon.png" "$BUILD_DIR/ui/" 2>/dev/null || true
        
        # Read the custom splash screen content
        SPLASH_CONTENT=$(cat "$SOURCE_DIR/ui/splash_screen.html")
        
        # Use python to safely replace the multi-line block, as sed is tricky with newlines
        # We replace the entire <figure ... id="qtspinner"> ... </figure> block
        python3 -c "
import sys
import re

html_path = '$HTML_FILE'
splash_path = '$SOURCE_DIR/ui/splash_screen.html'

with open(html_path, 'r') as f:
    content = f.read()

with open(splash_path, 'r') as f:
    new_splash = f.read()

# Regex to find the qtspinner figure block
# It looks for <figure ... id=\"qtspinner\"> ... </figure>
# We use re.DOTALL to match across newlines
pattern = r'<figure[^>]*id=\"qtspinner\"[^>]*>.*?</figure>'

new_content = re.sub(pattern, new_splash, content, flags=re.DOTALL)

with open(html_path, 'w') as f:
    f.write(new_content)
"
        echo "🌐 Starting application with emrun..."
        emrun "$HTML_FILE"
    else
        echo "⚠️  Warning: HTML wrapper not found at $HTML_FILE"
        echo "   You may need to run the app manually from the build directory."
    fi
else
    echo "❌ Build failed."
    exit 1
fi
