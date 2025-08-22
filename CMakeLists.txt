cmake_minimum_required(VERSION 3.16)
project(sdl2_tiny LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

add_executable(sdl_bounce
    main.cpp
    Ball.cpp
    Ball.hpp
    Rectangle.cpp
    Rectangle.hpp
    CollisionSystem.cpp
    CollisionSystem.hpp)
target_include_directories(sdl_bounce PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})
target_link_libraries(sdl_bounce PRIVATE ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(sdl_bounce PRIVATE -Wall -Wextra -Wpedantic)
endif()
