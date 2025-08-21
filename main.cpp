#include <SDL2/SDL.h>
#include <cstdlib>
#include "Ball.hpp"
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

    // Create ball instances with different colors
    Ball ball1(W / 2.0f, H / 2.0f, 122.0f, 40.0f, 12,
               0, 180, 255);  // Blue ball
    Ball ball2((W / 2.0f) - 200, (H / 2.0f), - 40.0f, 20.0f, 12,
               255, 100, 0);  // Orange ball

    Uint32 last = SDL_GetTicks();
    bool running = true;

    while (running) {
        // --- Events ---
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) running = false;
        }

        // --- Update ---
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        ball1.update(dt);
        ball2.update(dt);
        
        // Handle screen edge collisions
        CollisionSystem::handleEdgeCollision(ball1, W, H);
        CollisionSystem::handleEdgeCollision(ball2, W, H);
        
        // Check for collision between balls
        if (CollisionSystem::checkBallCollision(ball1, ball2)) {
            CollisionSystem::resolveBallCollision(ball1, ball2);
        }

        // --- Draw ---
        SDL_SetRenderDrawColor(ren, 245, 245, 145, 255); // background
        SDL_RenderClear(ren);

        ball1.render(ren);
        ball2.render(ren);

        // HUD text is skipped to keep it minimal

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
