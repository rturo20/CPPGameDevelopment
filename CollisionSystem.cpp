#include "CollisionSystem.hpp"
#include <cmath>

bool CollisionSystem::checkBallCollision(const Ball& ball1, const Ball& ball2) {
    // Calculate distance between ball centers
    float dx = ball2.getX() - ball1.getX();
    float dy = ball2.getY() - ball1.getY();
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Collision occurs when distance is less than sum of radii
    return distance < (ball1.getRadius() + ball2.getRadius());
}

void CollisionSystem::resolveBallCollision(Ball& ball1, Ball& ball2) {
    // Calculate displacement vector between balls
    float dx = ball2.getX() - ball1.getX();
    float dy = ball2.getY() - ball1.getY();
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Normalize the displacement vector
    float nx = dx / distance;
    float ny = dy / distance;
    
    // Calculate relative velocity
    float dvx = ball2.getVX() - ball1.getVX();
    float dvy = ball2.getVY() - ball1.getVY();
    
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
    ball1.setVelocity(ball1.getVX() - j * nx, ball1.getVY() - j * ny);
    ball2.setVelocity(ball2.getVX() + j * nx, ball2.getVY() + j * ny);
    
    // Prevent balls from sticking together by separating them
    float overlap = (ball1.getRadius() + ball2.getRadius()) - distance;
    if (overlap > 0) {
        float separationX = (overlap * nx) / 2.0f;
        float separationY = (overlap * ny) / 2.0f;
        ball1.setPosition(ball1.getX() - separationX, ball1.getY() - separationY);
        ball2.setPosition(ball2.getX() + separationX, ball2.getY() + separationY);
    }
}

void CollisionSystem::handleEdgeCollision(Ball& ball, int screenWidth, int screenHeight) {
    float x = ball.getX();
    float y = ball.getY();
    float vx = ball.getVX();
    float vy = ball.getVY();
    int radius = ball.getRadius();
    
    // Handle collisions with screen boundaries
    if (x < radius) {
        ball.setPosition(radius, y);
        ball.setVelocity(-vx, vy);
    }
    if (x > screenWidth - radius) {
        ball.setPosition(screenWidth - radius, y);
        ball.setVelocity(-vx, vy);
    }
    if (y < radius) {
        ball.setPosition(x, radius);
        ball.setVelocity(vx, -vy);
    }
    if (y > screenHeight - radius) {
        ball.setPosition(x, screenHeight - radius);
        ball.setVelocity(vx, -vy);
    }
}
