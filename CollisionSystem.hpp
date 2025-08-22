#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "Ball.hpp"
#include <vector>

class CollisionSystem {
public:
    // Methods for handling individual ball collisions
    static bool checkBallCollision(const Ball& ball1, const Ball& ball2);
    static void resolveBallCollision(Ball& ball1, Ball& ball2);
    static void handleEdgeCollision(Ball& ball, int screenWidth, int screenHeight);

    // Methods for handling multiple balls
    static void handleBallCollisions(std::vector<Ball>& balls);
    static void handleAllEdgeCollisions(std::vector<Ball>& balls, int screenWidth, int screenHeight);

private:
    // Private constructor to prevent instantiation
    CollisionSystem() = delete;
};

#endif // COLLISION_SYSTEM_HPP
