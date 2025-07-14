#!/bin/bash

echo "========================================"
echo "AI IMAGER by 119 - Build Script"
echo "========================================"
echo

# Check if git is available
if ! command -v git &> /dev/null; then
    echo "ERROR: Git is not installed"
    echo "Please install Git and try again"
    exit 1
fi

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake is not installed"
    echo "Please install CMake and try again"
    exit 1
fi

echo "Setting up JUCE submodule..."
git submodule update --init --recursive
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to initialize JUCE submodule"
    exit 1
fi

echo
echo "Creating build directory..."
mkdir -p build
cd build

echo
echo "Configuring with CMake..."

# Detect OS and set appropriate generator
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    cmake .. -G "Xcode"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Linux
    cmake .. -G "Unix Makefiles"
else
    # Fallback
    cmake ..
fi

if [ $? -ne 0 ]; then
    echo "ERROR: CMake configuration failed"
    exit 1
fi

echo
echo "Building plugin..."
cmake --build . --config Release
if [ $? -ne 0 ]; then
    echo "ERROR: Build failed"
    exit 1
fi

echo
echo "========================================"
echo "Build completed successfully!"
echo "========================================"
echo
echo "The plugin should be located in:"
echo "build/AIImager_artefacts/Release/VST3/"
echo
echo "You can now load AI IMAGER in your DAW!"
echo 