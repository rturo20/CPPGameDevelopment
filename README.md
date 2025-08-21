# SDL2 Ball Collision Demo

A simple 2D physics demo showcasing ball-to-ball collisions and screen boundary interactions using SDL2. The project demonstrates clean code organization with separation of concerns between ball physics and collision handling.

## Features

- Elastic ball-to-ball collisions
- Screen boundary collisions
- Smooth ball movement with delta time
- Modern C++ implementation
- Clean separation between entity and physics systems

## Project Structure

- `Ball.hpp/cpp`: Ball entity class handling position, velocity, and rendering
- `CollisionSystem.hpp/cpp`: Static collision detection and resolution system
- `main.cpp`: Game loop and SDL2 initialization
- `CMakeLists.txt`: CMake build configuration

## Dependencies

- SDL2
- SDL2_gfx (for circle rendering)
- CMake (>= 3.16)
- C++17 compatible compiler

## Building

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
make

# Run the demo
./sdl_bounce
```

## Controls

- ESC: Exit the application
- The demo runs automatically, showing two balls bouncing and colliding

## Implementation Details

The project follows good software engineering practices:

- **Separation of Concerns**: Collision detection and resolution are handled by a dedicated system rather than being embedded in the Ball class
- **Modern C++**: Uses C++17 features and follows modern C++ practices
- **Clean Architecture**: Clear separation between entity (Ball) and physics (CollisionSystem) components
- **Efficient Collision Detection**: Uses simple but effective circle-circle collision detection
- **Delta Time**: Movement is frame-rate independent using delta time

## License

This project is open source and available under the MIT License.
