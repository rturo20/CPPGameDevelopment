#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>

class Ball {
public:
    Ball(float x, float y, float vx, float vy, int radius, 
         Uint8 r = 0, Uint8 g = 180, Uint8 b = 255, Uint8 a = 255);
    
    void update(float dt);
    void render(SDL_Renderer* renderer) const;
    
    // Getters
    inline float getX() const { return x_; }
    inline float getY() const { return y_; }
    inline float getVX() const { return vx_; }
    inline float getVY() const { return vy_; }
    inline int getRadius() const { return radius_; }
    
    // Setters
    inline void setPosition(float x, float y) { x_ = x; y_ = y; }
    inline void setVelocity(float vx, float vy) { vx_ = vx; vy_ = vy; }
    
private:
    float x_, y_;        // Position
    float vx_, vy_;      // Velocity
    int radius_;         // Radius
    Uint8 r_, g_, b_, a_; // Color components
};

#endif // BALL_HPP
