#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>
class CollisionSystem;  // Forward declaration

class Ball {
public:
    Ball(float x, float y, float vx, float vy, int radius, 
         Uint8 r = 0, Uint8 g = 180, Uint8 b = 255, Uint8 a = 255);
    
    void update(float dt);
    void render(SDL_Renderer* renderer) const;
    
    // Velocity control methods
    void setVelocityX(float vx) { vx_ = vx; }
    void setVelocityY(float vy) { vy_ = vy; }
    float getVelocityX() const { return vx_; }
    float getVelocityY() const { return vy_; }
    
    // Position and size getters
    float getX() const { return x_; }
    float getY() const { return y_; }
    int getRadius() const { return radius_; }
    
    // Position setter
    void setX(float x) { x_ = x; }
    
    // Give CollisionSystem access to the Ball class's private members
    friend class CollisionSystem;  
    
private:
    float x_, y_;        // Position
    float vx_, vy_;      // Velocity
    int radius_;         // Radius
    Uint8 r_, g_, b_, a_; // Color components
};

#endif // BALL_HPP
