#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sstream>
#include "Ball.hpp"
#include "Rectangle.hpp"
#include "CollisionSystem.hpp"
#include "HUD.hpp"

int main() {
    const int W = 640, H = 360; // set window size

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) return 1; // initialize SDL

    // Create window
    SDL_Window*   win = SDL_CreateWindow("SDL2: tiniest bounce",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        W, H, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS); 
    if (!win) return 2; // check if window was created

    // Create renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1,
                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) return 3; // check if renderer was created

    // Create HUD, player rectangle and ball
    HUD hud(W, H);
    Rectangle player(W / 10.0f, H / 2.0f, 0.0f, 0.0f, 10, 60,  // 30x60 rectangle
                     100, 180, 255);  // Blue rectangle
    Ball ball1((W / 2.0f) - 200, (H / 2.0f), - 80.0f, 60.0f, 8,
                255, 100, 0); 

    
    Uint32 last = SDL_GetTicks();
    bool running = true;

    while (running) {
        // --- Events ---
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
                         if (e.type == SDL_KEYDOWN) {
                 if (e.key.keysym.sym == SDLK_ESCAPE) {
                     running = false;
                 }
                 // Control player with arrow keys
                 const float SPEED = 200.0f;
                 switch (e.key.keysym.sym) {
                     case SDLK_UP:    player.setVelocityY(-SPEED); break;
                     case SDLK_DOWN:  player.setVelocityY(SPEED); break;
                 }
             }
             // Stop player when keys are released
             else if (e.type == SDL_KEYUP) {
                 switch (e.key.keysym.sym) {
                     case SDLK_UP:    if (player.getVelocityY() < 0) player.setVelocityY(0); break;
                     case SDLK_DOWN:  if (player.getVelocityY() > 0) player.setVelocityY(0); break;
                 }
             }
        }

        // --- Update ---
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        player.update(dt);
        ball1.update(dt);
         
         // Keep player within vertical screen bounds
         if (player.getY() - player.getHeight()/2 < 0) {
             player.setVelocityY(0);
             player.setY(player.getHeight()/2);  // Set to top boundary
         }
         if (player.getY() + player.getHeight()/2 > H) {
             player.setVelocityY(0);
             player.setY(H - player.getHeight()/2);  // Set to bottom boundary
         }
         
         // Handle ball edge collisions
         CollisionSystem::handleEdgeCollision(ball1, W, H);
         
         // Check for collision between paddle and ball
         player.checkAndResolveCollision(ball1);

        // --- Draw ---
        SDL_SetRenderDrawColor(ren, 20, 25, 145, 255); // background
        SDL_RenderClear(ren);

        player.render(ren);
        ball1.render(ren);

        // Render HUD
        hud.render(ren, SDL_GetTicks() / 1000.0f);

        SDL_RenderPresent(ren);
    }


    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
