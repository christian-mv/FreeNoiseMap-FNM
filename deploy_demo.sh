#!/bin/bash
set -e

# ==============================================================================
# Deployment Script for Free Noise Map Demo
# ==============================================================================

PROJECT_ROOT="$(pwd)"
REPO_URL="git@github.com:christian-mv/christian-mv.github.io.git"
TARGET_DIR="Free_Noise_Map_Demo"
BUILD_DIR="build_wasm_release/ui"
TEMP_DEPLOY_DIR="/tmp/fnm_deploy_$(date +%s)"

# Helper function for user confirmation
confirm() {
    read -p "$1 (y/n): " choice
    case "$choice" in 
        y|Y ) echo "Processing...";;
        n|N ) echo "❌ Aborted."; exit 1;;
        * ) echo "Invalid input. Please answer y or n."; confirm "$1";;
    esac
}

# 1. Verify Build Artifacts
echo "Step 1: Verify Build Artifacts"
echo "Check if '$BUILD_DIR/FreeNoiseMap.html' and '$BUILD_DIR/FreeNoiseMap.wasm' exist."
if [ ! -f "$BUILD_DIR/FreeNoiseMap.html" ] || [ ! -f "$BUILD_DIR/FreeNoiseMap.wasm" ]; then
    echo "⚠️  Build artifacts not found."
    confirm "Do you want to run the build script './build_wasm_release.sh' now?"
    ./build_wasm_release.sh
    
    if [ ! -f "$BUILD_DIR/FreeNoiseMap.html" ]; then
        echo "❌ Error: Build failed or artifacts missing."
        exit 1
    fi
else
    confirm "Build artifacts found. Proceed?"
fi

# 2. Clone the Repository
echo -e "\nStep 2: Clone Repository"
echo "Repo URL: $REPO_URL"
echo "Temp Dir: $TEMP_DEPLOY_DIR"
confirm "Do you want to clone the repository to the temporary directory?"

echo "⬇️  Cloning $REPO_URL..."
git clone --depth 1 "$REPO_URL" "$TEMP_DEPLOY_DIR"

if [ ! -d "$TEMP_DEPLOY_DIR/$TARGET_DIR" ]; then
    echo "📁 Creating target directory: $TARGET_DIR"
    mkdir -p "$TEMP_DEPLOY_DIR/$TARGET_DIR"
fi

# 3. Update Files
echo -e "\nStep 3: Update Files"
echo "Target Dir: $TEMP_DEPLOY_DIR/$TARGET_DIR"
echo "Action: Remove contents of target dir and copy new build artifacts."
confirm "Do you want to proceed with updating the files?"

echo "♻️  Updating files in $TARGET_DIR..."

# Navigate to the target directory inside the repo
cd "$TEMP_DEPLOY_DIR/$TARGET_DIR"

# Remove old files (carefully)
rm -rf *

# Copy new files
# Note: We keep the original filename FreeNoiseMap.html as requested
cp "$PROJECT_ROOT/$BUILD_DIR/FreeNoiseMap.html" .
cp "$PROJECT_ROOT/$BUILD_DIR/FreeNoiseMap.js" .
cp "$PROJECT_ROOT/$BUILD_DIR/FreeNoiseMap.wasm" .
cp "$PROJECT_ROOT/$BUILD_DIR/qtloader.js" .
cp "$PROJECT_ROOT/$BUILD_DIR/app_icon.png" . 2>/dev/null || true

# List the changes
echo "Files prepared for commit:"
ls -l

# 4. Commit and Push
echo -e "\nStep 4: Commit and Push"
echo "Message: Update Free Noise Map Demo - $(date +'%Y-%m-%d %H:%M')"
echo "Branch: master"
confirm "Do you want to stage, commit, and push these changes to origin/master?"

echo "📦 Committing changes..."
git add .
git commit -m "Update Free Noise Map Demo - $(date +'%Y-%m-%d %H:%M')"

echo "🚀 Pushing to remote..."
git push origin master

# 5. Cleanup
echo -e "\nStep 5: Cleaning up..."
cd "$PROJECT_ROOT"
rm -rf "$TEMP_DEPLOY_DIR"

echo "✅ Deployment complete! Check https://christian-mv.github.io/$TARGET_DIR/FreeNoiseMap.html"