#ifndef HUD_HPP
#define HUD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iomanip>

#define INITIAL_LIVES 3

class HUD {
public:
    HUD(int screenWidth, int screenHeight);
    ~HUD();
    
    void init();  // Initialize TTF and load font
    void render(SDL_Renderer* renderer, float);
    
    // Setters for game stats
    void setLives(int lives) { lives_ = lives; }
    void setScore(int score) { score_ = score; }
    
private:
    TTF_Font* font_;
    int screenWidth_;
    int screenHeight_;
    int lives_;
    int score_;
    
    void renderText(SDL_Renderer* renderer, const std::string& text, 
                   int x, int y, SDL_Color color);
};

#endif // HUD_HPP
