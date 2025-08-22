#include <SDL2/SDL.h>
#include <cstdlib>
#include "Ball.hpp"
#include "Rectangle.hpp"
#include "CollisionSystem.hpp"

int main() {
    const int W = 640, H = 360;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) return 1;

    SDL_Window*   win = SDL_CreateWindow("SDL2: tiniest bounce",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        W, H, SDL_WINDOW_SHOWN);
    if (!win) return 2;

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1,
                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) return 3;

         // Create player rectangle and ball
         Rectangle player(W / 2.0f, H / 2.0f, 0.0f, 0.0f, 15, 60,  // 15x60 paddle at center
                     0, 180, 255);  // Blue rectangle
    Ball ball2((W / 2.0f) - 200, (H / 2.0f), - 40.0f, 20.0f, 12,
               255, 100, 0);  // Orange ball

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
                 // Control ball1 with arrow keys
                 const float SPEED = 200.0f;
                 switch (e.key.keysym.sym) {
                     case SDLK_UP:    player.setVelocityY(-SPEED); break;
                     case SDLK_DOWN:  player.setVelocityY(SPEED); break;
                 }
             }
             // Stop ball1 when keys are released
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
         ball2.update(dt);
         
         // Keep player within screen bounds (vertical only)
         if (player.getY() - player.getHeight()/2 < 0) player.setVelocityY(0);
         if (player.getY() + player.getHeight()/2 > H) player.setVelocityY(0);
         
         // Handle ball edge collisions
         CollisionSystem::handleEdgeCollision(ball2, W, H);
         
         // Check for collision between paddle and ball
         player.checkAndResolveCollision(ball2);

        // --- Draw ---
        SDL_SetRenderDrawColor(ren, 245, 245, 145, 255); // background
        SDL_RenderClear(ren);

                 player.render(ren);
         ball2.render(ren);

        // HUD text is skipped to keep it minimal

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
