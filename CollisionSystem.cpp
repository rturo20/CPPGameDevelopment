#include "CollisionSystem.hpp"
#include <cmath>

bool CollisionSystem::checkBallCollision(const Ball& ball1, const Ball& ball2) {
    // Calculate distance between ball centers
    float dx = ball2.x_ - ball1.x_;
    float dy = ball2.y_ - ball1.y_;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Collision occurs when distance is less than sum of radii
    return distance < (ball1.radius_ + ball2.radius_);
}

void CollisionSystem::resolveBallCollision(Ball& ball1, Ball& ball2) {
    // Calculate displacement vector between balls
    float dx = ball2.x_ - ball1.x_;
    float dy = ball2.y_ - ball1.y_;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Normalize the displacement vector
    float nx = dx / distance;
    float ny = dy / distance;
    
    // Calculate relative velocity
    float dvx = ball2.vx_ - ball1.vx_;
    float dvy = ball2.vy_ - ball1.vy_;
    
    // Calculate relative velocity along the normal
    float velocityAlongNormal = dvx * nx + dvy * ny;
    
    // Don't resolve if balls are moving apart
    if (velocityAlongNormal > 0) return;
    
    // Calculate restitution (bounciness) - 1.0 for perfect elastic collision
    const float restitution = 1.0f;
    
    // Calculate impulse scalar
    float j = -(1.0f + restitution) * velocityAlongNormal;
    j /= 2.0f;  // Assuming equal mass for both balls
    
    // Apply impulse
    ball1.vx_ -= j * nx;
    ball1.vy_ -= j * ny;
    ball2.vx_ += j * nx;
    ball2.vy_ += j * ny;
    
    // Prevent balls from sticking together by separating them
    float overlap = (ball1.radius_ + ball2.radius_) - distance;
    if (overlap > 0) {
        float separationX = (overlap * nx) / 2.0f;
        float separationY = (overlap * ny) / 2.0f;
        ball1.x_ -= separationX;
        ball1.y_ -= separationY;
        ball2.x_ += separationX;
        ball2.y_ += separationY;
    }
}

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
