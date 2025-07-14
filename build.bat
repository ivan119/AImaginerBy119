@echo off
echo ========================================
echo AI IMAGER by 119 - Build Script
echo ========================================
echo.

REM Check if git is available
git --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Git is not installed or not in PATH
    echo Please install Git and try again
    pause
    exit /b 1
)

REM Check if CMake is available
cmake --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: CMake is not installed or not in PATH
    echo Please install CMake and try again
    pause
    exit /b 1
)

echo Setting up JUCE submodule...
git submodule update --init --recursive
if errorlevel 1 (
    echo ERROR: Failed to initialize JUCE submodule
    pause
    exit /b 1
)

echo.
echo Creating build directory...
if not exist build mkdir build
cd build

echo.
echo Configuring with CMake...
cmake .. -G "Visual Studio 16 2019" -A x64
if errorlevel 1 (
    echo ERROR: CMake configuration failed
    pause
    exit /b 1
)

echo.
echo Building plugin...
cmake --build . --config Release
if errorlevel 1 (
    echo ERROR: Build failed
    pause
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo The plugin should be located in:
echo build\AIImager_artefacts\Release\VST3\
echo.
echo You can now load AI IMAGER in your DAW!
echo.
pause 