#include "Rectangle.hpp"
#include "Ball.hpp"
#include <algorithm>

Rectangle::Rectangle(float x, float y, float vx, float vy, int width, int height,
                    Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : x_(x), y_(y), vx_(vx), vy_(vy), width_(width), height_(height),
      r_(r), g_(g), b_(b), a_(a) {}

void Rectangle::update(float dt) {
    x_ += vx_ * dt;
    y_ += vy_ * dt;
}

void Rectangle::render(SDL_Renderer* renderer) const {
    SDL_Rect rect = {
        static_cast<int>(x_ - width_/2),
        static_cast<int>(y_ - height_/2),
        width_,
        height_
    };
    SDL_SetRenderDrawColor(renderer, r_, g_, b_, a_);
    SDL_RenderFillRect(renderer, &rect);
}

bool Rectangle::checkAndResolveCollision(Ball& ball) {
    // Get ball's position and radius using getters
    float ballX = ball.getX();
    float ballY = ball.getY();
    float ballRadius = ball.getRadius();
    
    // Calculate rectangle's bounds
    float rectLeft = x_ - width_/2;
    float rectRight = x_ + width_/2;
    float rectTop = y_ - height_/2;
    float rectBottom = y_ + height_/2;
    
    // Find the closest point on the rectangle to the ball
    float closestX = std::max(rectLeft, std::min(ballX, rectRight));
    float closestY = std::max(rectTop, std::min(ballY, rectBottom));
    
    // Calculate distance between closest point and ball center
    float distanceX = ballX - closestX;
    float distanceY = ballY - closestY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;
    
    // Check if we have a collision
    if (distanceSquared <= (ballRadius * ballRadius)) {
        // Collision detected! Reverse ball's x velocity
        ball.setVelocityX(-ball.getVelocityX());
        
        // Move ball outside of paddle
        if (ballX < x_) {
            ball.setX(rectLeft - ballRadius);
        } else {
            ball.setX(rectRight + ballRadius);
        }
        
        return true;
    }
    return false;
}
