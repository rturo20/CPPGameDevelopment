#include "CollisionSystem.hpp"
#include <cmath>

void CollisionSystem::handleEdgeCollision(Ball& ball, int screenWidth, int screenHeight) {
    // Handle collisions with screen boundaries
    if (ball.x_ < ball.radius_) {
        ball.x_ = ball.radius_;
        ball.vx_ = -ball.vx_;
    }
    if (ball.x_ > screenWidth - ball.radius_) {
        ball.x_ = screenWidth - ball.radius_;
        ball.vx_ = -ball.vx_;
    }
    if (ball.y_ < ball.radius_) {
        ball.y_ = ball.radius_;
        ball.vy_ = -ball.vy_;
    }
    if (ball.y_ > screenHeight - ball.radius_) {
        ball.y_ = screenHeight - ball.radius_;
        ball.vy_ = -ball.vy_;
    }
}