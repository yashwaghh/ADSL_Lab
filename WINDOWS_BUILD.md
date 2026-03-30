# Windows Build Instructions for Smart Text Editor

## Prerequisites

### Option 1: Using MSYS2 (Recommended)

1. **Install MSYS2** (if not already installed):
   - Download from: https://www.msys2.org/
   - Run the installer and follow the instructions
   - Open MSYS2 MinGW 64-bit terminal

2. **Install ncurses and build tools**:
   ```bash
   pacman -S --noconfirm base-devel mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc mingw-w64-x86_64-ncurses
   ```

3. **Build the project**:
   ```bash
   cd d:\\Mini_project_college_ADSl
   mkdir build
   cd build
   cmake ..
   make
   ```

### Option 2: Using WSL (Windows Subsystem for Linux)

1. **Install WSL2**:
   ```powershell
   wsl --install
   ```

2. **Install dependencies in WSL**:
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential cmake libncurses-dev
   ```

3. **Build the project**:
   ```bash
   cd /mnt/d/Mini_project_college_ADSl
   mkdir build
   cd build
   cmake ..
   make
   ```

### Option 3: Using vcpkg (C++ Package Manager)

1. **Clone vcpkg**:
   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.bat
   ```

2. **Install ncurses**:
   ```bash
   ./vcpkg install ncurses:x64-windows
   ```

3. **Build with vcpkg integration**:
   ```bash
   cd d:\\Mini_project_college_ADSl
   mkdir build
   cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
   cmake --build . --config Release
   ```

## Building from Windows Command Prompt

If you have MinGW compiler installed, you can try:

```batch
cd d:\Mini_project_college_ADSl\build
cmake -G "Unix Makefiles" ..
make
```

Or with Ninja (if installed):

```batch
cmake -G "Ninja" ..
ninja
```

## Troubleshooting

**Error: "Could NOT find Curses"**
- This means ncurses is not installed
- Follow one of the installation options above
- Ensure the library path is in your system PATH

**Error: C++ compiler not found**
- Install MinGW64 with C++ compiler
- Add MinGW bin folder to PATH environment variable
- Download from: https://www.mingw-w64.org/

**CMake not found**
- Download from: https://cmake.org/download/
- Add CMake bin folder to PATH

## Quick Setup with Batch Script

Save this as `setup-build.bat`:

```batch
@echo off
echo Building Smart Text Editor...
cd /d %~dp0
if not exist build mkdir build
cd build
cmake ..
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed. Please check dependencies.
    pause
    exit /b 1
)
echo Build successful! Output in: %cd%\bin
pause
```

Then double-click the batch file to build.

## After Building

The executable will be in `build\bin\smart_editor.exe`

Run it with:
```bash
./bin/smart_editor.exe
```

Or open a file:
```bash
./bin/smart_editor.exe path/to/file.cpp
```
