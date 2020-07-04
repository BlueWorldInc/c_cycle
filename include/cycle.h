#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <sdl_circle.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GROUND_Y SCREEN_HEIGHT * 0.75

typedef struct Cycle Cycle;
struct Cycle {
    int cycleX;
};

void drawWorld(SDL_Renderer *renderer, Cycle* cycle);
void drawCycle(SDL_Renderer* renderer, Cycle* cycle);
void drawRock(SDL_Renderer* renderer, Cycle* cycle);