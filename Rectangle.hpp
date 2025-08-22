#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

class Ball;  // Forward declaration

class Rectangle {
public:
    Rectangle(float x, float y, float vx, float vy, int width, int height,
             Uint8 r = 0, Uint8 g = 180, Uint8 b = 255, Uint8 a = 255);
    
    void update(float dt);
    void render(SDL_Renderer* renderer) const;
    
    // Velocity control methods
    void setVelocityX(float vx) { vx_ = vx; }
    void setVelocityY(float vy) { vy_ = vy; }
    float getVelocityX() const { return vx_; }
    float getVelocityY() const { return vy_; }
    
    // Position getters and setters
    float getX() const { return x_; }
    float getY() const { return y_; }
    void setX(float x) { x_ = x; }
    void setY(float y) { y_ = y; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    
    // Check and resolve collision with a ball
    bool checkAndResolveCollision(Ball& ball);
    
private:
    float x_, y_;        // Position (center)
    float vx_, vy_;      // Velocity
    int width_, height_; // Dimensions
    Uint8 r_, g_, b_, a_; // Color components
};

#endif // RECTANGLE_HPP
