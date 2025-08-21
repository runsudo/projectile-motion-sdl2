#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480
#define GRAVITY 9.81

const int radius = 5;

struct Circle {
    int x;
    int y;
    double radius;
    double vx;
    double vy;
    double dampening;
};


void draw_body(SDL_Renderer *renderer, struct Circle *circle);
void update_pos(SDL_Renderer *renderer, struct Circle *circle);

int main(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL2...\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Projectile Motion Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if (!window) {
        fprintf(stderr, "Error initializing window...\n");
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "Error initializing window...\n");
        return 1;
    }
    
    struct Circle circle = {radius, HEIGHT-radius, radius, 3, 7, .5};
    
    SDL_Event event;
    
    int is_game_running = 1;
    
    while (is_game_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                is_game_running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        
        draw_body(renderer, &circle);

        update_pos(renderer, &circle);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
    
}

void draw_body(SDL_Renderer *renderer, struct Circle *circle)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = circle->x-circle->radius; i<circle->x+circle->radius; i++)
    {
        for (int j = circle->y-circle->radius; j<circle->y+circle->radius; j++)
        {
            double dist = sqrt(pow((i-circle->x),2) + pow((j-circle->y),2));
            if (dist < circle->radius)
            {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }  
    }
}

void update_pos(SDL_Renderer *renderer, struct Circle *circle)
{

    circle->x = circle->x + circle->vx;
    circle->y = circle->y - circle->vy;

    circle->vy = circle->vy - GRAVITY * 0.016;

    if (circle->x < 0+radius)
    {
        circle->x = radius;
        circle->vx = -circle->vx;
        circle->vx *= circle->dampening;  
        circle->vy *= circle->dampening;  
    }

    if (circle->x > WIDTH-radius)
    {
        circle->x = WIDTH-radius;
        circle->vx = -circle->vx;
        circle->vx *= circle->dampening;
        circle->vy *= circle->dampening;  
    }

    if (circle->y < 0+radius)
    {
        circle->y = radius;
        circle->vy = -circle->vy;
        circle->vy *= circle->dampening;  
        circle->vy *= circle->dampening;  
    }

    if (circle->y > HEIGHT-radius)
    {
        circle->y = HEIGHT-radius;
        circle->vy = -circle->vy;
        circle->vy *= circle->dampening;  
        circle->vy *= circle->dampening;  
    }

}