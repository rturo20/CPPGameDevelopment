#include "HUD.hpp"

HUD::HUD(int screenWidth, int screenHeight)
    : font_(nullptr)
    , screenWidth_(screenWidth)
    , screenHeight_(screenHeight)
    , lives_(INITIAL_LIVES)
    , score_(0) {
    init();
}

HUD::~HUD() {
    if (font_) {
        TTF_CloseFont(font_);
    }
    TTF_Quit();
}

void HUD::init() {
    if (TTF_Init() == -1) {
        // In a real game, you'd want proper error handling here
        SDL_Log("TTF_Init failed: %s\n", TTF_GetError());
        return;
    }
    
    font_ = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
    if (!font_) {
        SDL_Log("Failed to load font: %s\n", TTF_GetError());
    }
}

void HUD::renderText(SDL_Renderer* renderer, const std::string& text, 
                    int x, int y, SDL_Color color) {
    if (!font_) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            SDL_Rect rect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

void HUD::render(SDL_Renderer* renderer, float) {  // elapsedTime parameter not used anymore
    SDL_Color white = {255, 255, 255, 255};
    const int MARGIN = 10;  // Margin from screen edges
    
    // Render score in top right
    std::stringstream scoreText;
    scoreText << "Score: " << score_;
    renderText(renderer, scoreText.str(), screenWidth_ - 100, MARGIN, white);
    
    // Render lives in bottom right
    std::stringstream livesText;
    livesText << "Lives: " << lives_;
    renderText(renderer, livesText.str(), screenWidth_ - 100, screenHeight_ - 30, white);
}
