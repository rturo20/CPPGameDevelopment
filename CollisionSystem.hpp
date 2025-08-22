#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "Ball.hpp"

class CollisionSystem {
public:
    static void handleEdgeCollision(Ball& ball, int screenWidth, int screenHeight);

private:
    // Private constructor to prevent instantiation
    CollisionSystem() = delete;
};

#endif // COLLISION_SYSTEM_HPP