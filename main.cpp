#include <SDL2/SDL.h>
#include <cstdlib>
#include <vector>
#include <random>
#include "Ball.hpp"
#include "CollisionSystem.hpp"

// Helper function to create a random ball
Ball createRandomBall(int screenWidth, int screenHeight) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    // Random position distributions
    std::uniform_real_distribution<float> x_dist(50.0f, screenWidth - 50.0f);
    std::uniform_real_distribution<float> y_dist(50.0f, screenHeight - 50.0f);
    
    // Random velocity distributions (-200 to 200)
    std::uniform_real_distribution<float> vel_dist(-200.0f, 200.0f);
    
    // Random radius distribution (5 to 15)
    std::uniform_int_distribution<int> radius_dist(5, 15);

    // Random color distributions
    std::uniform_int_distribution<int> color_dist(0, 255);
    
    return Ball(x_dist(gen), y_dist(gen),
               vel_dist(gen), vel_dist(gen),
               radius_dist(gen),  // Random radius between 5 and 15
               color_dist(gen), color_dist(gen), color_dist(gen));
}

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

    // Create a vector of balls with pre-allocated capacity
    const int NUM_BALLS = 1;  // You can adjust this number
    std::vector<Ball> balls;
    balls.reserve(NUM_BALLS * 2);  // Reserve extra space for balls added via spacebar
    
    // Initialize balls with random positions, velocities, and colors
    for (int i = 0; i < NUM_BALLS; ++i) {
        balls.push_back(createRandomBall(W, H));
    }

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
                } else if (e.key.keysym.sym == SDLK_SPACE) {
                    // Add a new ball when spacebar is pressed
                    balls.push_back(createRandomBall(W, H));
                    printf("Balls: %zu, Capacity: %zu\n", balls.size(), balls.capacity());
                }
            }
        }

        // --- Update ---
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        // Update all balls
        for (Ball& ball : balls) {
            ball.update(dt);
        }
        
        // Handle all collisions
        CollisionSystem::handleAllEdgeCollisions(balls, W, H);
        CollisionSystem::handleBallCollisions(balls);

        // --- Draw ---
        SDL_SetRenderDrawColor(ren, 245, 25, 145, 255); // background
        SDL_RenderClear(ren);

        // Render all balls
        for (const Ball& ball : balls) {
            ball.render(ren);
        }

        // HUD text is skipped to keep it minimal

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
