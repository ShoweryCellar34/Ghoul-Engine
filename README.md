
# What is Ghoul Engine?

Ghoul Engine is an OpenGL rendering engine \(I don't realy know what I'm doing with the project, but I know I'll use OpenGL for rendering\).

## Platform support

Ghoul Engine uses strictly cross-platform libraries \(Windows, Mac, and Linux support\) and [CMake](https://cmake.org/), and is tested on Arch linux X11 (with GNOME, idk if that matters), and has been tested on Windows 11/10.

## Disclaimer
1. Wayland is not supported as the restrictions on windows position query and modification with imgui \(internaly imgui calls a fuction that segfaults on wayland, may fix in futer DO NOT EXPECT\).
2. kdialog or another compatible package is required for tinyfiledialogs to fuction.
3. Using linux works, but it is buggier that windows.

## How to clone

run this command with [git](https://git-scm.com/) installed to clone this repository: `git clone --recursive https://github.com/ShoweryCellar34/Ghoul-Engine.git`

## How to build \(CMake required\)

Warning: the "res/" directory may not be copyed over to the binary directory when using MSVC.
### Windows \([Visual Studio](https://visualstudio.microsoft.com/)\)
1. Move into the cloned directory `cd Ghoul-Engine`.
2. Make the build directory `mkdir build` and move into it `cd build`.
3. Generate the project file `cmake -G"Visual Studio 17 2022" ./..` \(using Visual Studio 17 for this example\).
4. open the solution and then build it and run the "Ghoul-Engine" project.

### Windows \(MinGW 32-bit\)

1. Move into the cloned directory `cd Ghoul-Engine`.
2. Make the build directory `mkdir build` and move into it `cd build`.
3. Generate the project file `cmake -G"MinGW Makefiles" ./..`.
4. Build Ghoul Engine with `mingw32-make` and run the produced `Ghoul-Engine.exe` file.

### Ubuntu \(GCC\)

1. Move into the cloned directory `cd Ghoul-Engine`.
2. Make the build directory `mkdir build` and move into it `cd build`.
3. Generate the project file `cmake -G"Unix Makefiles" ./..`.
4. Build Ghoul Engine with `make` and run the produced `Ghoul-Engine` file.
