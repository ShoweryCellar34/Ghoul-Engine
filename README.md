### What is Ghoul Engine?
Ghoul Engine is an OpenGL rendering engine (I don't realy know what I'm doing with the project, but I know I'll use OpenGL for rendering).

## Platform support
Ghoul Engine uses strictly cross-platform libraries \(Windows, Mac, and Linux support\) and [CMake](https://cmake.org/), and is primary tested on Windows 11 but has been tested on Ubuntu 24.

## How to clone
run this command with [git](https://git-scm.com/) installed to clone this repository: `git clone --recursive https://github.com/ShoweryCellar34/Ghoul-Engine.git`

## How to build (CMake only)
### Windows (Visual Studio 17)
1. Move into the cloned directory `cd Ghoul-Engine`
2. Make the build directory `mkdir build` and move into it `cd build`
3. Generate the project file `cmake -G"Visual Studio 17 2022" ./..`
4. open the solution and then build it and run the "Ghoul-Engine" project.

### Windows (MinGW 32-bit)
1. Move into the cloned directory `cd Ghoul-Engine`
2. Make the build directory `mkdir build` and move into it `cd build`
3. Generate the project file `cmake -G"MinGW Makefiles" ./..`
4. Build Ghoul Engine with `mingw32-make` and run with the produced `Ghoul-Engine.exe` file.
