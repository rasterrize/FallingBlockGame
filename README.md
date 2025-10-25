# FallingBlockGame

![gameplay](https://github.com/rasterrize/FallingBlockGame/raw/master/screenshot.png)

A fun little tetris clone built in C++ using my own [*pxlFramework*](https://github.com/rasterrize/pxlFramework).

Currently, it only runs on Windows.

### Clone, build, and run

To build you will need:
 - [CMake](https://cmake.org/download/) (_any recent version_)
 - [VulkanSDK](https://vulkan.lunarg.com/sdk/home) (_with **Shader Toolchain Debug Symbols x64**, **Vulkan Memory Allocator header** and **Volk header** checked_)
 - [MSVC](https://visualstudio.microsoft.com/downloads/) (_any version supporting **C++20**_)

Clone the repository using:
```sh
git clone https://github.com/rasterrize/FallingBlockGame
```

Run CMake with your IDE, or manually use these commands:
```
cd FallingBlockGame
mkdir build
cd build
cmake ..
```

And build with:
```
cmake --build .
```

**IMPORTANT:** To run the game you will need to take the built executable found in the **build/Debug** folder and move it to the **build/bin** folder, so it has access to the game files.

### Controls (keyboard only)
- A or Left arrow: Move block left
- D or Right arrow: Move block right
- S or Down arrow: Soft drop
- Q or Z: Rotate left
- E or X: Rotate right
- Space: Hard drop
- Shift: Hold block
- R: Start new game

### Currently implemented functionality
- The 7 classic tetris blocks
- Block placing and rotating
- Block bag showing the upcoming player blocks
- Line clears
- Block holding

### Functionality and improvements I wish to add
- Scoring system
- All the special rotations found in games like [Tetr.io](https://tetr.io/)
- Correct block bag at the start (1 of each block)
- Mathematically correct block randomness (it's [garbage](https://youtu.be/tdFNA7YBM4c?si=ZvevQpMfnZjeRNQi) atm)
- Better movement controls for the player block
- Additional time for rotation clears (like T-spins)

### Upcoming features
- Alternative game modes
- Cool animations and shaders
- Controller support
- Steam deck support (Which also means linux support!)
- Custom skins
- Main menu
- Settings menu (settings andy friendly)
