#include "Ball.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>

Ball::Ball(float x, float y, float vx, float vy, int radius, 
         Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : x_(x), y_(y), vx_(vx), vy_(vy), radius_(radius),
      r_(r), g_(g), b_(b), a_(a) {}

void Ball::update(float dt) {
    // Update position
    x_ += vx_ * dt;
    y_ += vy_ * dt;
}

void Ball::render(SDL_Renderer* renderer) const {
    // Draw the ball using SDL2_gfx's filled circle function
    filledCircleRGBA(renderer, 
                     static_cast<Sint16>(x_), 
                     static_cast<Sint16>(y_), 
                     static_cast<Sint16>(radius_),
                     r_,   // Red
                     g_,   // Green
                     b_,   // Blue
                     a_    // Alpha
    );
}
